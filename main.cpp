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

#include "HuaweiMe906.hpp"

#include "stm32f7xx_hal.h"

#include "usbh_core.h"

#include "distortos/board/initializeStreams.hpp"
#include "distortos/board/standardOutputStream.h"

#include "distortos/assert.h"
#include "distortos/ThisThread.hpp"

#include <cinttypes>

namespace
{

/**
 * \brief User callback for USB host events.
 *
 * \param [in] host is a pointer to USB host
 * \param [in] event is the event
 */

void usbHostEventCallback(USBH_HandleTypeDef*, const uint8_t event)
{
	switch(event)
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
