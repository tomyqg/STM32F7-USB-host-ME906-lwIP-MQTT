/**
 * \file
 * \brief Definitions of lwIP functions related to TCP/IP core locking
 *
 * \author Copyright (C) 2019 Kamil Szczygiel http://www.distortec.com http://www.freddiechopin.info
 *
 * \par License
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#include "lwip/tcpip.h"

#include "distortos/internal/CHECK_FUNCTION_CONTEXT.hpp"

#include "distortos/ThisThread.hpp"
#include "distortos/ThreadIdentifier.hpp"

namespace
{

/*---------------------------------------------------------------------------------------------------------------------+
| local objects
+---------------------------------------------------------------------------------------------------------------------*/

/// true it lwIP's TCP/IP thread is started, false otherwise
bool tcpipThreadStarted;

/// identifier of the thread which locked lwIP's TCP/IP core
distortos::ThreadIdentifier lockHolderThreadIdentifier;

}	// namespace

/*---------------------------------------------------------------------------------------------------------------------+
| global functions
+---------------------------------------------------------------------------------------------------------------------*/

void lwipAssertCoreLocked()
{
	CHECK_FUNCTION_CONTEXT();

	if (tcpipThreadStarted == false)
		return;

	LWIP_ASSERT("Function called without core lock", lockHolderThreadIdentifier.getThread() != nullptr &&
			lockHolderThreadIdentifier == distortos::ThisThread::getIdentifier());
}

void lwipLockTcpipCore()
{
	sys_mutex_lock(&lock_tcpip_core);
	lockHolderThreadIdentifier = distortos::ThisThread::getIdentifier();
}

void lwipMarkTcpipThread()
{
	tcpipThreadStarted = true;
}

void lwipUnlockTcpipCore()
{
	lockHolderThreadIdentifier = {};
	sys_mutex_unlock(&lock_tcpip_core);
}
