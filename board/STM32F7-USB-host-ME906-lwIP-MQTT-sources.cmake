#
# file: STM32F7-USB-host-ME906-lwIP-MQTT-sources.cmake
#
# author: Copyright (C) 2019 Kamil Szczygiel http://www.distortec.com http://www.freddiechopin.info
#
# This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
# distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
#

target_include_directories(STM32F7-USB-host-ME906-lwIP-MQTT PRIVATE
		${CMAKE_CURRENT_LIST_DIR}/include)
target_sources(STM32F7-USB-host-ME906-lwIP-MQTT PRIVATE
		${CMAKE_CURRENT_LIST_DIR}/initializeStreams.cpp)
