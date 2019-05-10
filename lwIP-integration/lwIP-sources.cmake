#
# file: lwIP-sources.cmake
#
# author: Copyright (C) 2019 Kamil Szczygiel http://www.distortec.com http://www.freddiechopin.info
#
# This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
# distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
#

add_library(lwIP-integration STATIC
		${CMAKE_CURRENT_LIST_DIR}/lwipCriticalSection.cpp
		${CMAKE_CURRENT_LIST_DIR}/lwipMailbox.cpp
		${CMAKE_CURRENT_LIST_DIR}/lwipMiscellaneous.cpp
		${CMAKE_CURRENT_LIST_DIR}/lwipMutex.cpp
		${CMAKE_CURRENT_LIST_DIR}/lwipSemaphore.cpp
		${CMAKE_CURRENT_LIST_DIR}/lwipTcpipCoreLocking.cpp
		${CMAKE_CURRENT_LIST_DIR}/lwipTime.cpp)
target_include_directories(lwIP-integration PUBLIC
		${CMAKE_CURRENT_LIST_DIR}/include
		${LWIP_INCLUDE_DIRS})
target_link_libraries(lwIP-integration PUBLIC
		distortos::distortos)

target_link_libraries(lwipcore PUBLIC
		lwIP-integration)
target_link_libraries(lwipallapps PUBLIC
		lwIP-integration)
