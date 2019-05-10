/**
 * \file
 * \brief Definitions of time-related functions for lwIP
 *
 * \author Copyright (C) 2019 Kamil Szczygiel http://www.distortec.com http://www.freddiechopin.info
 *
 * \par License
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#include "lwip/sys.h"

#include "distortos/TickClock.hpp"

/*---------------------------------------------------------------------------------------------------------------------+
| global functions
+---------------------------------------------------------------------------------------------------------------------*/

u32_t sys_jiffies()
{
	return distortos::TickClock::now().time_since_epoch().count();
}

u32_t sys_now()
{
	return std::chrono::milliseconds{distortos::TickClock::now().time_since_epoch()}.count();
}
