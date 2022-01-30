# SPDX-License-Identifier: Apache-2.0

cmake_minimum_required(VERSION 3.20.0)

#Board selection inside zephyr
#set (BOARD adafruit_feather_m0_basic_proto)
#set(BOARD nrf52840dk_nrf52840)
#set(BOARD nrf5340pdk_nrf5340_cpunet)
#set(BOARD nrf5340pdk_nrf5340_cpuapp)
set(BOARD skb501_nrf52840)
#set(BOARD nrf52840dk_nrf52811)

#Board selection outside zephyr
set(BOARD_ROOT ${CMAKE_CURRENT_SOURCE_DIR})

#Toolchain selection
#set(TOOLCHAIN C:/gnuarmemb)

#Zephyr selection
#set(ZEPHYR_BASE C:/Users/raffa/Github/zephyrproject/zephyr)



find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})

project(NONE)

target_sources(app PRIVATE src/main.c)
