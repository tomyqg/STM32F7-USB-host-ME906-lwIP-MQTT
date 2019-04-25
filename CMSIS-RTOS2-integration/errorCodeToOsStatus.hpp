/**
 * \file
 * \brief errorCodeToOsStatus() declaration
 *
 * \author Copyright (C) 2019 Kamil Szczygiel http://www.distortec.com http://www.freddiechopin.info
 *
 * \par License
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef CMSIS_RTOS2_INTEGRATION_ERRORCODETOOSSTATUS_HPP_
#define CMSIS_RTOS2_INTEGRATION_ERRORCODETOOSSTATUS_HPP_

#include "cmsis_os.h"

/**
 * \brief Converts error code to CMSIS-RTOS2 OS status.
 *
 * \param [in] errorCode is an error code
 *
 * \return \a errorCode converted to CMSIS-RTOS2 OS status
 */

osStatus_t errorCodeToOsStatus(int errorCode);

#endif	// CMSIS_RTOS2_INTEGRATION_ERRORCODETOOSSTATUS_HPP_
