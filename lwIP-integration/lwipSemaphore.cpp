/**
 * \file
 * \brief Definitions of semaphore-related functions for lwIP
 *
 * \author Copyright (C) 2019 Kamil Szczygiel http://www.distortec.com http://www.freddiechopin.info
 *
 * \par License
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#include "lwip/sys.h"

#include "distortos/assert.h"
#include "distortos/TickClock.hpp"

#include <cerrno>
#include <cstring>

namespace
{

/*---------------------------------------------------------------------------------------------------------------------+
| local objects
+---------------------------------------------------------------------------------------------------------------------*/

/// distortos_Semaphore in an invalid state, real object will never match this one
const struct distortos_Semaphore invalidSemaphore {};

}	// namespace

/*---------------------------------------------------------------------------------------------------------------------+
| global functions
+---------------------------------------------------------------------------------------------------------------------*/

u32_t sys_arch_sem_wait(sys_sem_t* const semaphore, const u32_t timeoutMs)
{
	const auto duration = distortos::TickClock::duration{std::chrono::milliseconds{timeoutMs}}.count();
	const auto ret = timeoutMs == 0 ? distortos_Semaphore_wait(semaphore) :
			distortos_Semaphore_tryWaitFor(semaphore, duration);
	assert(ret == 0 || ret == ETIMEDOUT);
	static_assert(SYS_ARCH_TIMEOUT != 0);
	return ret == 0 ? 0 : SYS_ARCH_TIMEOUT;
}

void sys_sem_free(sys_sem_t* const semaphore)
{
	const auto ret = distortos_Semaphore_destruct(semaphore);
	assert(ret == 0);
}

err_t sys_sem_new(sys_sem_t* const semaphore, const u8_t count)
{
	const auto ret = distortos_Semaphore_construct_1(semaphore, count, 1);
	assert(ret == 0);
	return ERR_OK;
}

void sys_sem_set_invalid(sys_sem_t* const semaphore)
{
	memcpy(semaphore, &invalidSemaphore, sizeof(*semaphore));
}

void sys_sem_signal(sys_sem_t* const semaphore)
{
	const auto ret = distortos_Semaphore_post(semaphore);
	assert(ret == 0 || ret == EOVERFLOW);
}

int sys_sem_valid(sys_sem_t* const semaphore)
{
	const auto ret = memcmp(semaphore, &invalidSemaphore, sizeof(*semaphore));
	return ret != 0;
}
