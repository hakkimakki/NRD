cmake_minimum_required(VERSION 3.8.2)

#Board selection inside zephyr
#set(BOARD nrf52840dk_nrf52840)
#set(BOARD nrf5340pdk_nrf5340_cpunet)
#set(BOARD nrf5340pdk_nrf5340_cpuapp)
set(BOARD nrf52840dongle_nrf52840)
#set(BOARD nrf52840dk_nrf52811)
#Board selection outside zephyr
#set(BOARD_ROOT ./board)

#Toolchain selection
#set(TOOLCHAIN C:/gnuarmemb)

#Zephyr selection
#set(ZEPHYR_BASE L:/Github/ncs/zephyr)
#set(ZEPHYR_BASE L:/Github/ncs-workspace-1.6.1/zephyr)

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})

project(NONE)

add_subdirectory_ifdef(CONFIG_SZL_ENABLE szl)

# Include all files in folder src
FILE(GLOB app_sources_c src/*.c)
FILE(GLOB app_sources_cpp src/*.cpp)

target_sources(app PRIVATE
	${app_sources_c} ${app_sources_cpp})

target_include_directories(app PRIVATE include)
