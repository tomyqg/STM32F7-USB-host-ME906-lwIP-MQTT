/**
 * \file
 * \brief lwipErrorToErrorCode() definition
 *
 * \author Copyright (C) 2019 Kamil Szczygiel http://www.distortec.com http://www.freddiechopin.info
 *
 * \par License
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#include "lwipErrorToErrorCode.hpp"

#include <cerrno>

/*---------------------------------------------------------------------------------------------------------------------+
| global functions
+---------------------------------------------------------------------------------------------------------------------*/

int lwipErrorToErrorCode(const err_t error)
{
	static const int errorCodes[]
	{
			0,				// ERR_OK, 0
			ENOMEM,			// ERR_MEM, -1 - out of memory error
			ENOBUFS,		// ERR_BUF, -2 - buffer error
			ETIMEDOUT,		// ERR_TIMEOUT, -3 - timeout
			EHOSTUNREACH,	// ERR_RTE, -4 - routing problem
			EINPROGRESS,	// ERR_INPROGRESS, -5 - operation in progress
			EINVAL,			// ERR_VAL, -6 - illegal value
			EWOULDBLOCK,	// ERR_WOULDBLOCK, -7 - operation would block
			EADDRINUSE,		// ERR_USE, -8 - address in use
			EINPROGRESS,	// ERR_ALREADY, -9 - already connecting
			EISCONN,		// ERR_ISCONN, -10 - connection already established
			ENOTCONN,		// ERR_CONN, -11 - not connected
			EIO,			// ERR_IF, -12 - low-level netif error
			ECONNABORTED,	// ERR_ABRT, -13 - connection aborted
			ENETRESET,		// ERR_RST, -14 - connection reset
			ENOTCONN,		// ERR_CLSD, -15 - connection closed
			EINVAL,			// ERR_ARG, -16 - illegal argument
	};

	if (error > 0 || static_cast<size_t>(-error) >= sizeof(errorCodes) / sizeof(*errorCodes))
		return EINVAL;

	return errorCodes[-error];
}
