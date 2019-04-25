/**
 * \file
 * \brief Definitions of CMSIS-RTOS2 functions related to message queues
 *
 * \author Copyright (C) 2019 Kamil Szczygiel http://www.distortec.com http://www.freddiechopin.info
 *
 * \par License
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#include "errorCodeToOsStatus.hpp"

#include "distortos/assert.h"
#include "distortos/DynamicRawMessageQueue.hpp"

/*---------------------------------------------------------------------------------------------------------------------+
| global functions
+---------------------------------------------------------------------------------------------------------------------*/

osMessageQueueId_t osMessageQueueNew(const uint32_t queueSize, const uint32_t elementSize, const osMessageQueueAttr_t*)
{
	const auto queue = new distortos::DynamicRawMessageQueue{elementSize, queueSize};
	assert(queue != nullptr);
	return queue;
}

osStatus_t osMessageQueuePut(const osMessageQueueId_t queue, const void* const message, const uint8_t priority,
		const uint32_t timeoutMs)
{
	assert(queue != nullptr);
	assert(message != nullptr);
	auto& rawMessageQueue = *static_cast<distortos::DynamicRawMessageQueue*>(queue);
	const auto elementSize = rawMessageQueue.getElementSize();
	const auto ret = timeoutMs == 0 ? rawMessageQueue.tryPush(priority, message, elementSize) :
			timeoutMs == osWaitForever ? rawMessageQueue.push(priority, message, elementSize) :
			rawMessageQueue.tryPushFor(std::chrono::milliseconds{timeoutMs}, priority, message, elementSize);
	return errorCodeToOsStatus(ret);
}

osStatus_t osMessageQueueGet(const osMessageQueueId_t queue, void* const message, uint8_t* priority,
		const uint32_t timeoutMs)
{
	assert(queue != nullptr);
	assert(message != nullptr);
	uint8_t dummyPriority;
	if (priority == nullptr)
		priority = &dummyPriority;
	auto& rawMessageQueue = *static_cast<distortos::DynamicRawMessageQueue*>(queue);
	const auto elementSize = rawMessageQueue.getElementSize();
	const auto ret = timeoutMs == 0 ? rawMessageQueue.tryPop(*priority, message, elementSize) :
			timeoutMs == osWaitForever ? rawMessageQueue.pop(*priority, message, elementSize) :
			rawMessageQueue.tryPopFor(std::chrono::milliseconds{timeoutMs}, *priority, message, elementSize);
	return errorCodeToOsStatus(ret);
}
