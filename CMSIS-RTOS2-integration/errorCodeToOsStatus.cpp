/**
 * \file
 * \brief errorCodeToOsStatus() definition
 *
 * \author Copyright (C) 2019 Kamil Szczygiel http://www.distortec.com http://www.freddiechopin.info
 *
 * \par License
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#include "errorCodeToOsStatus.hpp"

#include <cerrno>

/*---------------------------------------------------------------------------------------------------------------------+
| global functions
+---------------------------------------------------------------------------------------------------------------------*/

osStatus_t errorCodeToOsStatus(const int errorCode)
{
	if (errorCode == 0)
		return osOK;
	if (errorCode == ETIMEDOUT)
		return osErrorTimeout;
	if (errorCode == EBUSY)
		return osErrorResource;
	if (errorCode == EINVAL)
		return osErrorParameter;
	if (errorCode == ENOMEM)
		return osErrorNoMemory;

	return osError;
}
