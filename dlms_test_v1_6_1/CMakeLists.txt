#
# Copyright (c) 2019 Nordic Semiconductor ASA
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

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(NONE)

# Include all files in folder src
FILE(GLOB app_sources_c src/*.c)
#FILE(GLOB dlms_sources_c dlms/src/*.c)
#FILE(GLOB dlms_sources_h dlms/include/*.h)
FILE(GLOB app_sources_cpp src/*.cpp)

target_sources(app PRIVATE
	${app_sources_c}
	${app_sources_cpp}
	#${dlms_sources_c}
	#${dlms_sources_h}
	dlms/src/client.c dlms/include/gxignore.h dlms/src/apdu.c dlms/src/bitarray.c dlms/src/bytebuffer.c dlms/src/ciphering.c dlms/src/converters.c dlms/src/cosem.c dlms/src/datainfo.c 
	dlms/src/date.c 
	dlms/src/dlms.c dlms/src/dlmsSettings.c dlms/src/gxaes.c dlms/src/gxarray.c dlms/src/gxget.c dlms/src/gxinvoke.c dlms/src/gxkey.c dlms/src/gxmd5.c dlms/src/gxobjects.c dlms/src/gxset.c dlms/src/gxsha1.c dlms/src/gxsha256.c dlms/src/gxvalueeventargs.c dlms/src/helpers.c dlms/src/message.c dlms/src/notify.c dlms/src/objectarray.c dlms/src/parameters.c dlms/src/replydata.c dlms/src/server.c dlms/src/variant.c
	)

target_include_directories(app PRIVATE include)
