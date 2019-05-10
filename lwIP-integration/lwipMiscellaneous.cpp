/**
 * \file
 * \brief Definitions of miscellaneous functions for lwIP
 *
 * \author Copyright (C) 2019 Kamil Szczygiel http://www.distortec.com http://www.freddiechopin.info
 *
 * \par License
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#include "lwip/sys.h"

#include "distortos/DynamicThread.hpp"
#include "distortos/ThreadIdentifier.hpp"

static_assert(sizeof(sys_thread_t) == sizeof(distortos::ThreadIdentifier) &&
		alignof(sys_thread_t) == alignof(distortos::ThreadIdentifier),
		"sys_thread_t doesn't match distortos::ThreadIdentifier!");

/*---------------------------------------------------------------------------------------------------------------------+
| global functions
+---------------------------------------------------------------------------------------------------------------------*/

void sys_init()
{

}

sys_thread_t sys_thread_new(const char*, const lwip_thread_fn function, void* const argument, const int stackSize,
		const int priority)
{
	auto thread = distortos::makeAndStartDynamicThread({static_cast<size_t>(stackSize), static_cast<uint8_t>(priority)},
			function, argument);
	const auto identifier = thread.getIdentifier();
	const auto ret = thread.detach();
	assert(ret == 0);
	return *reinterpret_cast<const sys_thread_t*>(&identifier);
}
