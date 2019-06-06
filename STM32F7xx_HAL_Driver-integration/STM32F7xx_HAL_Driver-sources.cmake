#
# file: STM32F7xx_HAL_Driver-sources.cmake
#
# author: Copyright (C) 2019 Kamil Szczygiel http://www.distortec.com http://www.freddiechopin.info
#
# This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
# distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
#

add_library(STM32F7xx_HAL_Driver-integration STATIC
		${CMAKE_CURRENT_LIST_DIR}/HAL_Delay.cpp)
target_link_libraries(STM32F7xx_HAL_Driver-integration PUBLIC
		STM32F7xx_HAL_Driver)

add_library(STM32F7xx_HAL_Driver::STM32F7xx_HAL_Driver ALIAS STM32F7xx_HAL_Driver-integration)
