/**
 * \file
 * \brief CMSIS-RTOS2 osDelay() definition
 *
 * \author Copyright (C) 2019 Kamil Szczygiel http://www.distortec.com http://www.freddiechopin.info
 *
 * \par License
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#include "errorCodeToOsStatus.hpp"

#include "distortos/ThisThread.hpp"

/*---------------------------------------------------------------------------------------------------------------------+
| global functions
+---------------------------------------------------------------------------------------------------------------------*/

osStatus_t osDelay(const uint32_t milliseconds)
{
	const auto ret = distortos::ThisThread::sleepFor(std::chrono::milliseconds{milliseconds});
	return errorCodeToOsStatus(ret);
}
