/**
 * \file
 * \brief CMSIS-RTOS2 osThreadNew() definition
 *
 * \author Copyright (C) 2019 Kamil Szczygiel http://www.distortec.com http://www.freddiechopin.info
 *
 * \par License
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#include "cmsis_os.h"

#include "distortos/DynamicThread.hpp"

/*---------------------------------------------------------------------------------------------------------------------+
| global functions
+---------------------------------------------------------------------------------------------------------------------*/

osThreadId_t osThreadNew(const osThreadFunc_t function, void* const argument, const osThreadAttr_t* const attributes)
{
	assert(function != nullptr);
	assert(attributes != nullptr);
	assert(attributes->priority <= UINT8_MAX);
	const auto thread = new distortos::DynamicThread{{attributes->stack_size,
			static_cast<uint8_t>(attributes->priority)}, function, argument};
	assert(thread != nullptr);
	const auto ret = thread->start();
	assert(ret == 0);
	return thread;
}
