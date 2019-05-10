/**
 * \file
 * \brief Definitions of mutex-related functions for lwIP
 *
 * \author Copyright (C) 2019 Kamil Szczygiel http://www.distortec.com http://www.freddiechopin.info
 *
 * \par License
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#include "lwip/sys.h"

#include "distortos/assert.h"

#include <cstring>

namespace
{

/*---------------------------------------------------------------------------------------------------------------------+
| local objects
+---------------------------------------------------------------------------------------------------------------------*/

/// distortos_Mutex in an invalid state, real object will never match this one
const struct distortos_Mutex invalidMutex {};

}	// namespace

/*---------------------------------------------------------------------------------------------------------------------+
| global functions
+---------------------------------------------------------------------------------------------------------------------*/

void sys_mutex_free(sys_mutex_t* const mutex)
{
	const auto ret = distortos_Mutex_destruct(mutex);
	assert(ret == 0);
}

void sys_mutex_lock(sys_mutex_t* const mutex)
{
	const auto ret = distortos_Mutex_lock(mutex);
	assert(ret == 0);
}

err_t sys_mutex_new(sys_mutex_t* const mutex)
{
	const auto ret = distortos_Mutex_construct_1p(mutex, distortos_Mutex_Protocol_priorityInheritance);
	assert(ret == 0);
	return ERR_OK;
}

void sys_mutex_set_invalid(sys_mutex_t* const mutex)
{
	memcpy(mutex, &invalidMutex, sizeof(*mutex));
}

void sys_mutex_unlock(sys_mutex_t* const mutex)
{
	const auto ret = distortos_Mutex_unlock(mutex);
	assert(ret == 0);
}

int sys_mutex_valid(sys_mutex_t* const mutex)
{
	const auto ret = memcmp(mutex, &invalidMutex, sizeof(*mutex));
	return ret != 0;
}
