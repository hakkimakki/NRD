# SPDX-License-Identifier: Apache-2.0

cmake_minimum_required(VERSION 3.13.1)

#Board selection
set(BOARD nrf52840dk_nrf52840)
#set(BOARD nrf5340pdk_nrf5340_cpunet)
#set(BOARD nrf5340pdk_nrf5340_cpuapp)
#set(BOARD nrf52840dongle_nrf52840)
#set(BOARD nrf52840dk_nrf52811)

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(app)

target_sources(app PRIVATE src/main.c src/bm_simple_buttons_and_leds.c src/bm_at_modem.c src/bm_influxdb.c)

target_include_directories(app PRIVATE include)