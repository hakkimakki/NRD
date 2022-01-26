# SPDX-License-Identifier: Apache-2.0

cmake_minimum_required(VERSION 3.20.0)
find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(getchar)

target_sources(app PRIVATE src/main.c)

# DLMS Gurux Library
add_definitions(-DGX_DLMS_MICROCONTROLLER)
add_definitions(-DDLMS_IGNORE_IP6_SETUP)
add_definitions(-DDLMS_USE_EPOCH_TIME)
#add_definitions(-DDLMS_IGNORE_MALLOC)


FILE(GLOB dlms_sources_c GuruxDLMS_development/src/*.c)

target_sources(app PRIVATE ${dlms_sources_c})

target_include_directories(app PRIVATE GuruxDLMS_development/include)