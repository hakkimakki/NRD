#
# Copyright (c) 2020 Nordic Semiconductor ASA
#
# SPDX-License-Identifier: LicenseRef-Nordic-5-Clause
#
cmake_minimum_required(VERSION 3.8.2)

#Board selection
set(BOARD nrf52840dk_nrf52840)
#set(BOARD nrf5340pdk_nrf5340_cpunet)
#set(BOARD nrf5340pdk_nrf5340_cpuapp)
#set(BOARD nrf52840dongle_nrf52840)
#set(BOARD nrf52840dk_nrf52811)

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(NONE)

# NORDIC SDK APP START
target_sources(app PRIVATE
	src/main.c
	src/model_handler.c)
target_include_directories(app PRIVATE include)
# NORDIC SDK APP END
