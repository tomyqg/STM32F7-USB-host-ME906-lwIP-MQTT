/**
 * \file
 * \brief lwIP's sys_arch.h header for distortos
 *
 * \author Copyright (C) 2019 Kamil Szczygiel http://www.distortec.com http://www.freddiechopin.info
 *
 * \par License
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef LWIP_INTEGRATION_INCLUDE_ARCH_SYS_ARCH_H_
#define LWIP_INTEGRATION_INCLUDE_ARCH_SYS_ARCH_H_

#include "distortos/C-API/Mutex.h"
#include "distortos/C-API/Semaphore.h"

#ifdef __cplusplus
extern "C"
{
#endif	/* def __cplusplus */

/*---------------------------------------------------------------------------------------------------------------------+
| global types
+---------------------------------------------------------------------------------------------------------------------*/

/** struct with same size and alignment as distortos::DynamicRawFifoQueue */
struct distortos_DynamicRawFifoQueue
{
	/** implementation details */
	const void* implementation[14];
};

/** struct with same size and alignment as distortos::ThreadIdentifier */
struct distortos_ThreadIdentifier
{
	/** implementation details */
	const void* implementation[2];
};

/** lwIP mailbox */
typedef struct distortos_DynamicRawFifoQueue sys_mbox_t;

/** lwIP mutext */
typedef struct distortos_Mutex sys_mutex_t;

/** lwIP lightweight protection level */
typedef const void* sys_prot_t;

/** lwIP semaphore */
typedef struct distortos_Semaphore sys_sem_t;

/** lwIP thread */
typedef struct distortos_ThreadIdentifier sys_thread_t;

#ifdef __cplusplus
}	/* extern "C" */
#endif	/* def __cplusplus */

#endif	/* LWIP_INTEGRATION_INCLUDE_ARCH_SYS_ARCH_H_ */
