/**
 * \file
 * \brief Definition of openHuaweiMe906()
 *
 * \author Copyright (C) 2019 Kamil Szczygiel http://www.distortec.com http://www.freddiechopin.info
 *
 * \par License
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#define _GNU_SOURCE

#include "openHuaweiMe906.hpp"

#include "distortos/assert.h"

namespace
{

/*---------------------------------------------------------------------------------------------------------------------+
| local functions
+---------------------------------------------------------------------------------------------------------------------*/

/**
 * \brief Decodes `void*` cookie into `HuaweiMe906&` and `HuaweiMe906::Port`.
 *
 * \param [in] cookie is the cookie that will be decoded
 *
 * \return \a cookie decoded into a pair with `HuaweiMe906&` and `HuaweiMe906::Port`
 */

std::pair<HuaweiMe906&, HuaweiMe906::Port> decodeCookie(void* const cookie)
{
	auto& huaweiMe906 = *reinterpret_cast<HuaweiMe906*>(reinterpret_cast<uintptr_t>(cookie) & ~0b11);
	const auto port = static_cast<HuaweiMe906::Port>(reinterpret_cast<uintptr_t>(cookie) & 0b11);
	return {huaweiMe906, port};
}

/**
 * \brief Encodes `HuaweiMe906&` and `HuaweiMe906::Port` into `void*` cookie.
 *
 * \param [in] huaweiMe906 is a reference to HuaweiMe906 object that will be encoded
 * \param [in] port selects the serial port of \a huaweiMe906 that will be encoded
 *
 * \return \a huaweiMe906 and \a port encoded into `void*` cookie
 */

void* encodeCookie(HuaweiMe906& huaweiMe906, const HuaweiMe906::Port port)
{
	assert((reinterpret_cast<uintptr_t>(&huaweiMe906) & 0b11) == 0);
	assert((static_cast<uintptr_t>(port) & ~0b11) == 0);

	return reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(&huaweiMe906) | static_cast<uintptr_t>(port));
}

/**
 * \brief Wrapper for HuaweiMe906::read() which can be used with fopencookie()
 *
 * \param [in] cookie is a cookie which was passed to fopencookie(), must be HuaweiMe906 ORed with HuaweiMe906::Port!
 * \param [out] buffer is the buffer to which the data will be written
 * \param [in] size is the size of \a buffer, bytes
 *
 * \return number of read bytes on success, -1 otherwise
 */

ssize_t readHuaweiMe906(void* const cookie, char* const buffer, const size_t size)
{
	const auto [huaweiMe906, port] = decodeCookie(cookie);
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

ssize_t writeHuaweiMe906(void* const cookie, const char* const buffer, const size_t size)
{
	const auto [huaweiMe906, port] = decodeCookie(cookie);
	const auto ret = huaweiMe906.write(port, buffer, size);
	if (ret != 0)
	{
		errno = ret;
		return -1;
	}

	return size;
}

}	// namespace

/*---------------------------------------------------------------------------------------------------------------------+
| global functions
+---------------------------------------------------------------------------------------------------------------------*/

FILE* openHuaweiMe906(HuaweiMe906& huaweiMe906, const HuaweiMe906::Port port, const char* const mode)
{
	const auto stream = fopencookie(encodeCookie(huaweiMe906, port), mode, {readHuaweiMe906, writeHuaweiMe906, {}, {}});
	assert(stream != nullptr);

	{
		const auto ret = setvbuf(stream, nullptr, _IOLBF, 256);
		assert(ret == 0);
	}

	return stream;
}
