/**
 * \file
 * \brief Main code block.
 *
 * \author Copyright (C) 2019 Kamil Szczygiel http://www.distortec.com http://www.freddiechopin.info
 *
 * \par License
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#define _GNU_SOURCE

#include "HuaweiMe906.hpp"

#include "stm32f7xx_hal.h"

#include "usbh_core.h"

#include "distortos/board/initializeStreams.hpp"

#include "distortos/DynamicThread.hpp"
#include "distortos/ThisThread.hpp"

#include "lwip/tcpip.h"

#include <cstring>

namespace
{

/*---------------------------------------------------------------------------------------------------------------------+
| local functions
+---------------------------------------------------------------------------------------------------------------------*/

/**
 * \brief Wrapper for HuaweiMe906::read() which can be used with fopencookie()
 *
 * \param [in] cookie is a cookie which was passed to fopencookie(), must be HuaweiMe906 ORed with HuaweiMe906::Port!
 * \param [out] buffer is the buffer to which the data will be written
 * \param [in] size is the size of \a buffer, bytes
 *
 * \return number of read bytes on success, -1 otherwise
 */

ssize_t huaweiMe906Read(void* const cookie, char* const buffer, const size_t size)
{
	auto& huaweiMe906 = *reinterpret_cast<HuaweiMe906*>(reinterpret_cast<uintptr_t>(cookie) & ~0b11);
	const auto port = static_cast<HuaweiMe906::Port>(reinterpret_cast<uintptr_t>(cookie) & 0b11);
	const auto [ret, bytesRead] = huaweiMe906.read(port, buffer, size);
	if (ret != 0)
	{
		errno = ret;
		return -1;
	}

	return bytesRead;
}

/**
 * \brief Wrapper for HuaweiMe906::write() which can be used with fopencookie()
 *
 * \param [in] cookie is a cookie which was passed to fopencookie(), must be HuaweiMe906 ORed with HuaweiMe906::Port!
 * \param [in] buffer is the buffer with data that will be transmitted
 * \param [in] size is the size of \a buffer, bytes
 *
 * \return number of written bytes on success, -1 otherwise
 */

ssize_t huaweiMe906Write(void* const cookie, const char* const buffer, const size_t size)
{
	auto& huaweiMe906 = *reinterpret_cast<HuaweiMe906*>(reinterpret_cast<uintptr_t>(cookie) & ~0b11);
	const auto port = static_cast<HuaweiMe906::Port>(reinterpret_cast<uintptr_t>(cookie) & 0b11);
	const auto ret = huaweiMe906.write(port, buffer, size);
	if (ret != 0)
	{
		errno = ret;
		return -1;
	}

	return size;
}

/**
 * \brief Wraps selected HuaweiMe906 serial port into a FILE and sets line buffering.
 *
 * \param [in] huaweiMe906 is a reference to HuaweiMe906 object
 * \param [in] port selects the serial port that will be accessed
 * \param [in] mode is the mode with which the stream is opened
 *
 * \return pointer to opened FILE object
 */

FILE* openHuaweiMe906(HuaweiMe906& huaweiMe906, const HuaweiMe906::Port port, const char* const mode)
{
	assert((reinterpret_cast<uintptr_t>(&huaweiMe906) & 0b11) == 0);
	assert((static_cast<uintptr_t>(port) & ~0b11) == 0);

	const auto cookie =
			reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(&huaweiMe906) | static_cast<uintptr_t>(port));
	const auto stream = fopencookie(cookie, mode, {huaweiMe906Read, huaweiMe906Write, {}, {}});
	assert(stream != nullptr);

	{
		const auto ret = setvbuf(stream, nullptr, _IOLBF, 256);
		assert(ret == 0);
	}

	return stream;
}

/**
 * \brief Thread which constantly reads selected HuaweiMe906 serial port and prints data that was read on
 * \a standardOutputStream.
 *
 * \param [in] huaweiMe906 is a reference to HuaweiMe906 object
 * \param [in] port selects the serial port that will be accessed
 */

void readerThread(HuaweiMe906& huaweiMe906, const HuaweiMe906::Port port)
{
	const auto stream = openHuaweiMe906(huaweiMe906, port, "r");
	const auto portString = port == HuaweiMe906::Port::pcui ? "PCUI" :
			port == HuaweiMe906::Port::networkCard ? "Network card" : "GPS";

	while (1)
	{
		char buffer[128];
		if (fgets(buffer, sizeof(buffer), stream) != nullptr)
		{
			auto length = strlen(buffer);
			// trim trailing whitespace
			while (length > 0 && (buffer[length - 1] == '\r' || buffer[length - 1] == '\n'))
			{
				buffer[length - 1] = '\0';
				--length;
			}
			if (length > 0)
				fiprintf(standardOutputStream, "%s port, read %zu bytes: \"%s\"\r\n", portString, length, buffer);
		}
		else
		{
			fiprintf(standardOutputStream, "%s port, read failed, errno = %d\r\n", portString, errno);
			clearerr(stream);
			distortos::ThisThread::sleepFor(std::chrono::seconds{5});
		}
	}
}

/**
 * \brief User callback for USB host events.
 *
 * \param [in] host is a pointer to USB host
 * \param [in] event is the event
 */

void usbHostEventCallback(USBH_HandleTypeDef*, const uint8_t event)
{
	switch (event)
	{
		case HOST_USER_SELECT_CONFIGURATION:
			USBH_UsrLog("usbHostEventCallback: HOST_USER_SELECT_CONFIGURATION");
			break;

		case HOST_USER_CLASS_ACTIVE:
			USBH_UsrLog("usbHostEventCallback: HOST_USER_CLASS_ACTIVE");
			break;

		case HOST_USER_CLASS_SELECTED:
			USBH_UsrLog("usbHostEventCallback: HOST_USER_CLASS_SELECTED");
			break;

		case HOST_USER_CONNECTION:
			USBH_UsrLog("usbHostEventCallback: HOST_USER_CONNECTION");
			break;

		case HOST_USER_DISCONNECTION:
			USBH_UsrLog("usbHostEventCallback: HOST_USER_DISCONNECTION");
			break;

		case HOST_USER_UNRECOVERED_ERROR:
			USBH_UsrLog("usbHostEventCallback: HOST_USER_UNRECOVERED_ERROR");
			break;

		default:
			USBH_UsrLog("usbHostEventCallback: event = %" PRIu8, event);
			break;
	}
}

}	// namespace

/*---------------------------------------------------------------------------------------------------------------------+
| global functions
+---------------------------------------------------------------------------------------------------------------------*/

/**
 * \brief Main code block of application
 *
 * \return doesn't return
 */

int main()
{
	distortos::board::initializeStreams();

	fiprintf(standardOutputStream, "Started %s board\r\n", DISTORTOS_BOARD);

	USBH_HandleTypeDef usbHost {};
	{
		const auto ret = USBH_Init(&usbHost, usbHostEventCallback, 0);
		assert(ret == USBH_OK);

	}
	HuaweiMe906 huaweiMe906 {};
	huaweiMe906.registerClass(usbHost);
	{
		const auto ret = USBH_Start(&usbHost);
		assert(ret == USBH_OK);
	}

	const auto pcuiReaderThread = distortos::makeAndStartDynamicThread({2048, 1},
			readerThread, std::ref(huaweiMe906), HuaweiMe906::Port::pcui);
	const auto networkCardReaderThread = distortos::makeAndStartDynamicThread({2048, 1},
			readerThread, std::ref(huaweiMe906), HuaweiMe906::Port::networkCard);
	const auto gpsReaderThread = distortos::makeAndStartDynamicThread({2048, 1},
			readerThread, std::ref(huaweiMe906), HuaweiMe906::Port::gps);

	tcpip_init({}, {});

	while (1)
	{
#if USBH_USE_OS == 0
		USBH_Process(&usbHost);
		distortos::ThisThread::sleepFor(distortos::TickClock::duration{});
#else
		distortos::ThisThread::sleepFor(std::chrono::seconds{1});
#endif
	}
}

extern "C" void OTG_FS_IRQHandler(void)
{
	extern HCD_HandleTypeDef hhcd;
	HAL_HCD_IRQHandler(&hhcd);
}
