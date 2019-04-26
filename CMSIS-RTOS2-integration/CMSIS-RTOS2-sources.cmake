#
# file: CMSIS-RTOS2-sources.cmake
#
# author: Copyright (C) 2019 Kamil Szczygiel http://www.distortec.com http://www.freddiechopin.info
#
# This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
# distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
#

add_library(CMSIS-RTOS2-integration STATIC
		${CMAKE_CURRENT_LIST_DIR}/errorCodeToOsStatus.cpp
		${CMAKE_CURRENT_LIST_DIR}/osDelay.cpp
		${CMAKE_CURRENT_LIST_DIR}/osMessageQueue.cpp
		${CMAKE_CURRENT_LIST_DIR}/osThread.cpp)
target_include_directories(CMSIS-RTOS2-integration PUBLIC
		${CMAKE_CURRENT_LIST_DIR}/include
		$<TARGET_PROPERTY:CMSIS-RTOS2,INTERFACE_INCLUDE_DIRECTORIES>)
target_link_libraries(CMSIS-RTOS2-integration PUBLIC
		distortos::distortos)

target_link_libraries(CMSIS-RTOS2 INTERFACE
		CMSIS-RTOS2-integration)
