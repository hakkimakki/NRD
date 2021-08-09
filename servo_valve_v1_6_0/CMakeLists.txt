#
# Copyright (c) 2019 Nordic Semiconductor ASA
#
# SPDX-License-Identifier: LicenseRef-BSD-5-Clause-Nordic
#
cmake_minimum_required(VERSION 3.8.2)

#Board selection
#set(BOARD nrf52840dk_nrf52840)
#set(BOARD nrf5340pdk_nrf5340_cpunet)
#set(BOARD nrf5340pdk_nrf5340_cpuapp)
set(BOARD nrf52840dongle_nrf52840)
#set(BOARD nrf52840dk_nrf52811)

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(NONE)

# Include all files in folder src
FILE(GLOB app_sources_c src/*.c)
FILE(GLOB app_sources_cpp src/*.cpp)


target_sources(app PRIVATE
	${app_sources_c}
	${app_sources_cpp})
target_include_directories(app PRIVATE include)
