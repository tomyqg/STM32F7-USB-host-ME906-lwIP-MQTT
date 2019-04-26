#
# file: CMSIS-RTOS2-sources.cmake
#
# author: Copyright (C) 2019 Kamil Szczygiel http://www.distortec.com http://www.freddiechopin.info
#
# This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
# distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
#

add_library(CMSIS-RTOS2 INTERFACE)
target_include_directories(CMSIS-RTOS2 INTERFACE
		${CMAKE_CURRENT_LIST_DIR}/Include)
