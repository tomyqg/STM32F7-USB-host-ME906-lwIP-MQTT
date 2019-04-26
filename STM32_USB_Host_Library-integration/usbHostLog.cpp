/**
 * \file
 * \brief usbHostLog() definition
 *
 * \author Copyright (C) 2019 Kamil Szczygiel http://www.distortec.com http://www.freddiechopin.info
 *
 * \par License
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#include "usbh_conf.h"

#if USBH_DEBUG_LEVEL > 0

#include "distortos/architecture/isInInterruptContext.hpp"

#include "distortos/board/standardOutputStream.h"

#include "distortos/StaticThread.hpp"

#include "estd/ScopeGuard.hpp"

#include <cstdarg>

namespace
{

/*---------------------------------------------------------------------------------------------------------------------+
| local objects
+---------------------------------------------------------------------------------------------------------------------*/

/// buffers for calls to usbHostLog() from interrupts
char buffers[16][128];

/// semaphore for communication between usbHostLog() and \a backgroundThread
distortos::Semaphore semaphore {0};

/// background thread which prints messages sent from interrupts
const auto backgroundThread = distortos::makeAndStartStaticThread<1024>(UINT8_MAX, []()
		{
			size_t index {};
			while (1)
			{
				semaphore.wait();
				fputs(buffers[index], standardOutputStream);
				index = (index + 1) % (sizeof(buffers) / sizeof(*buffers));
			}
		});

}	// namespace

/*---------------------------------------------------------------------------------------------------------------------+
| global functions
+---------------------------------------------------------------------------------------------------------------------*/

extern "C" void usbHostLog(const char* const format, ...)
{
	static size_t bufferIndex;

	va_list arguments;
	va_start(arguments, format);
	const auto scopeGuard = estd::makeScopeGuard([&arguments]()
			{
				va_end(arguments);
			});

	if (distortos::architecture::isInInterruptContext() == true)
	{
		const auto index = bufferIndex;
		bufferIndex = (bufferIndex + 1) % (sizeof(buffers) / sizeof(*buffers));
		vsniprintf(buffers[index], sizeof(buffers[index]), format, arguments);
		semaphore.post();
		return;
	}

	vfiprintf(standardOutputStream, format, arguments);
}

#endif	// USBH_DEBUG_LEVEL > 0
