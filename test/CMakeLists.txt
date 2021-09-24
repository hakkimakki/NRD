#
# Copyright (c) 2018 Nordic Semiconductor
#
# SPDX-License-Identifier: LicenseRef-BSD-5-Clause-Nordic
#

cmake_minimum_required(VERSION 3.8.2)



#Board selection
set(BOARD nrf52840dk_nrf52840)
#set(BOARD nrf5340pdk_nrf5340_cpunet)
#set(BOARD nrf5340pdk_nrf5340_cpuapp)
#set(BOARD nrf52840dongle_nrf52840)
#set(BOARD nrf52840dk_nrf52811)

include($ENV{ZEPHYR_BASE}/cmake/app/boilerplate.cmake NO_POLICY_SCOPE)
project(NONE)



FILE(GLOB app_sources_cpp src/*.cpp)
FILE(GLOB dlms_sources_cpp dlms/src/*.cpp)

target_sources(app PRIVATE ${app_sources_cpp} ${dlms_sources_cpp})

target_include_directories(app PRIVATE dlms/..)