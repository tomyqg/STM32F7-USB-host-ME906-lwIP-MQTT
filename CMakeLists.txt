#
# file: CMakeLists.txt
#
# author: Copyright (C) 2019 Kamil Szczygiel http://www.distortec.com http://www.freddiechopin.info
#
# This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
# distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
#

cmake_minimum_required(VERSION 3.7)
project(STM32F7-USB-host-ME906-lwIP-MQTT)

#-----------------------------------------------------------------------------------------------------------------------
# distortos library
#-----------------------------------------------------------------------------------------------------------------------

add_subdirectory(distortos)

#-----------------------------------------------------------------------------------------------------------------------
# STM32F7-USB-host-ME906-lwIP-MQTT application
#-----------------------------------------------------------------------------------------------------------------------

add_executable(STM32F7-USB-host-ME906-lwIP-MQTT
		main.cpp)
target_link_libraries(STM32F7-USB-host-ME906-lwIP-MQTT PRIVATE
		distortos::distortos)
distortosTargetLinkerScripts(STM32F7-USB-host-ME906-lwIP-MQTT $ENV{DISTORTOS_LINKER_SCRIPT})

include(${CMAKE_CURRENT_LIST_DIR}/board/STM32F7-USB-host-ME906-lwIP-MQTT-sources.cmake)

distortosBin(STM32F7-USB-host-ME906-lwIP-MQTT STM32F7-USB-host-ME906-lwIP-MQTT.bin)
distortosDmp(STM32F7-USB-host-ME906-lwIP-MQTT STM32F7-USB-host-ME906-lwIP-MQTT.dmp)
distortosHex(STM32F7-USB-host-ME906-lwIP-MQTT STM32F7-USB-host-ME906-lwIP-MQTT.hex)
distortosLss(STM32F7-USB-host-ME906-lwIP-MQTT STM32F7-USB-host-ME906-lwIP-MQTT.lss)
distortosMap(STM32F7-USB-host-ME906-lwIP-MQTT STM32F7-USB-host-ME906-lwIP-MQTT.map)
distortosSize(STM32F7-USB-host-ME906-lwIP-MQTT)
