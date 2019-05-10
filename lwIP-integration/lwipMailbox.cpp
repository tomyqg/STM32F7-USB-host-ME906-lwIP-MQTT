/**
 * \file
 * \brief Definitions of mailbox-related functions for lwIP
 *
 * \author Copyright (C) 2019 Kamil Szczygiel http://www.distortec.com http://www.freddiechopin.info
 *
 * \par License
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#include "lwip/sys.h"

#include "distortos/assert.h"
#include "distortos/DynamicRawFifoQueue.hpp"

#include <cstring>

static_assert(sizeof(sys_mbox_t) == sizeof(distortos::DynamicRawFifoQueue) &&
		alignof(sys_mbox_t) == alignof(distortos::DynamicRawFifoQueue),
		"sys_mbox_t doesn't match distortos::DynamicRawFifoQueue!");

namespace
{

/*---------------------------------------------------------------------------------------------------------------------+
| local objects
+---------------------------------------------------------------------------------------------------------------------*/

/// distortos_DynamicRawFifoQueue in an invalid state, real object will never match this one
const distortos_DynamicRawFifoQueue invalidMailbox {};

}	// namespace

/*---------------------------------------------------------------------------------------------------------------------+
| global functions
+---------------------------------------------------------------------------------------------------------------------*/

u32_t sys_arch_mbox_fetch(sys_mbox_t* const mailbox, void** message, const u32_t timeoutMs)
{
	void* dummyMessage;
	if (message == nullptr)
		message = &dummyMessage;
	auto& dynamicRawFifoQueue = *reinterpret_cast<distortos::DynamicRawFifoQueue*>(mailbox);
	const auto ret = timeoutMs == 0 ? dynamicRawFifoQueue.pop(*message) :
			dynamicRawFifoQueue.tryPopFor(std::chrono::milliseconds{timeoutMs}, *message);
	assert(ret == 0 || ret == ETIMEDOUT);
	static_assert(SYS_ARCH_TIMEOUT != 0);
	return ret == 0 ? 0 : SYS_ARCH_TIMEOUT;
}

u32_t sys_arch_mbox_tryfetch(sys_mbox_t* const mailbox, void** message)
{
	void* dummyMessage;
	if (message == nullptr)
		message = &dummyMessage;
	auto& dynamicRawFifoQueue = *reinterpret_cast<distortos::DynamicRawFifoQueue*>(mailbox);
	const auto ret = dynamicRawFifoQueue.tryPop(*message);
	return ret == 0 ? 0 : SYS_MBOX_EMPTY;
}

void sys_mbox_free(sys_mbox_t* const mailbox)
{
	auto& dynamicRawFifoQueue = *reinterpret_cast<distortos::DynamicRawFifoQueue*>(mailbox);
	dynamicRawFifoQueue.~DynamicRawFifoQueue();
}

err_t sys_mbox_new(sys_mbox_t* const mailbox, const int size)
{
	new (mailbox) distortos::DynamicRawFifoQueue {sizeof(void*), static_cast<size_t>(size)};
	return ERR_OK;
}

void sys_mbox_post(sys_mbox_t* const mailbox, void* const message)
{
	auto& dynamicRawFifoQueue = *reinterpret_cast<distortos::DynamicRawFifoQueue*>(mailbox);
	const auto ret = dynamicRawFifoQueue.push(message);
	assert(ret == 0);
}

void sys_mbox_set_invalid(sys_mbox_t* const mailbox)
{
	memcpy(mailbox, &invalidMailbox, sizeof(*mailbox));
}

err_t sys_mbox_trypost(sys_mbox_t* const mailbox, void* const message)
{
	auto& dynamicRawFifoQueue = *reinterpret_cast<distortos::DynamicRawFifoQueue*>(mailbox);
	const auto ret = dynamicRawFifoQueue.tryPush(message);
	return ret == 0 ? ERR_OK : ERR_MEM;
}

err_t sys_mbox_trypost_fromisr(sys_mbox_t* const mailbox, void* message)
{
	return sys_mbox_trypost(mailbox, message);
}

int sys_mbox_valid(sys_mbox_t* const mailbox)
{
	const auto ret = memcmp(mailbox, &invalidMailbox, sizeof(*mailbox));
	return ret != 0;
}
