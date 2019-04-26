#
# file: STM32_USB_Host_Library-sources.cmake
#
# author: Copyright (C) 2019 Kamil Szczygiel http://www.distortec.com http://www.freddiechopin.info
#
# This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
# distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
#

add_library(STM32_USB_Host_Library-integration STATIC
		${CMAKE_CURRENT_LIST_DIR}/usbHostLog.cpp)
target_include_directories(STM32_USB_Host_Library-integration PUBLIC
		${CMAKE_CURRENT_LIST_DIR}/include
		$<TARGET_PROPERTY:STM32_USB_Host_Library,INTERFACE_INCLUDE_DIRECTORIES>)

target_link_libraries(STM32_USB_Host_Library PUBLIC
		STM32_USB_Host_Library-integration)
target_sources(STM32_USB_Host_Library PRIVATE
		${CMAKE_CURRENT_LIST_DIR}/usbh_conf.c)
