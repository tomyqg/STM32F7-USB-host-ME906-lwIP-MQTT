#
# file: STM32F7xx_HAL_Driver-sources.cmake
#
# author: Copyright (C) 2019 Kamil Szczygiel http://www.distortec.com http://www.freddiechopin.info
#
# This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
# distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
#

add_library(STM32F7xx_HAL_Driver STATIC
		${CMAKE_CURRENT_LIST_DIR}/Src/stm32f7xx_hal_cortex.c
		${CMAKE_CURRENT_LIST_DIR}/Src/stm32f7xx_hal_gpio.c
		${CMAKE_CURRENT_LIST_DIR}/Src/stm32f7xx_hal_hcd.c
		${CMAKE_CURRENT_LIST_DIR}/Src/stm32f7xx_ll_usb.c)
target_compile_options(STM32F7xx_HAL_Driver PRIVATE
		-Wno-attributes)
target_include_directories(STM32F7xx_HAL_Driver PUBLIC
		${CMAKE_CURRENT_LIST_DIR}/Inc)
