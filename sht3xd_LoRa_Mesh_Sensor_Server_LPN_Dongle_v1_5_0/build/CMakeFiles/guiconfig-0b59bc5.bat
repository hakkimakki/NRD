@echo off
cd /D D:\Raffael\GitHub\P6_Software_local\my_projects\NRD\sht3xd_LoRa_Mesh_Sensor_Server_LPN_Dongle_v1_5_0\build\zephyr\kconfig || (set FAIL_LINE=2& goto :ABORT)
"C:\Program Files\CMake\bin\cmake.exe" -E env ZEPHYR_BASE=D:/Raffael/GitHub/P6_Software_local/ncs/zephyr ZEPHYR_TOOLCHAIN_VARIANT=gnuarmemb PYTHON_EXECUTABLE=C:/Python38/python.exe srctree=D:/Raffael/GitHub/P6_Software_local/ncs/zephyr KERNELVERSION=0x2046300 KCONFIG_CONFIG=D:/Raffael/GitHub/P6_Software_local/my_projects/NRD/sht3xd_LoRa_Mesh_Sensor_Server_LPN_Dongle_v1_5_0/build/zephyr/.config ARCH=arm ARCH_DIR=D:/Raffael/GitHub/P6_Software_local/ncs/zephyr/arch BOARD_DIR=D:/Raffael/GitHub/P6_Software_local/ncs/zephyr/boards/arm/nrf52840dk_nrf52840 SHIELD_AS_LIST= KCONFIG_BINARY_DIR=D:/Raffael/GitHub/P6_Software_local/my_projects/NRD/sht3xd_LoRa_Mesh_Sensor_Server_LPN_Dongle_v1_5_0/build/Kconfig TOOLCHAIN_KCONFIG_DIR=D:/Raffael/GitHub/P6_Software_local/ncs/zephyr/cmake/toolchain/gnuarmemb EDT_PICKLE=D:/Raffael/GitHub/P6_Software_local/my_projects/NRD/sht3xd_LoRa_Mesh_Sensor_Server_LPN_Dongle_v1_5_0/build/zephyr/edt.pickle ZEPHYR_NRF_MODULE_DIR=D:/Raffael/GitHub/P6_Software_local/ncs/nrf ZEPHYR_MCUBOOT_MODULE_DIR=D:/Raffael/GitHub/P6_Software_local/ncs/bootloader/mcuboot ZEPHYR_MCUBOOT_KCONFIG=D:/Raffael/GitHub/P6_Software_local/ncs/nrf/modules/mcuboot/Kconfig ZEPHYR_NRFXLIB_MODULE_DIR=D:/Raffael/GitHub/P6_Software_local/ncs/nrfxlib ZEPHYR_TFM_MODULE_DIR=D:/Raffael/GitHub/P6_Software_local/ncs/modules/tee/tfm ZEPHYR_TFM_MCUBOOT_MODULE_DIR=D:/Raffael/GitHub/P6_Software_local/ncs/modules/tee/tfm-mcuboot ZEPHYR_CDDL_GEN_MODULE_DIR=D:/Raffael/GitHub/P6_Software_local/ncs/modules/lib/cddl-gen ZEPHYR_CDDL_GEN_KCONFIG=D:/Raffael/GitHub/P6_Software_local/ncs/nrf/modules/cddl-gen/Kconfig ZEPHYR_CMSIS_MODULE_DIR=D:/Raffael/GitHub/P6_Software_local/ncs/modules/hal/cmsis ZEPHYR_CANOPENNODE_MODULE_DIR=D:/Raffael/GitHub/P6_Software_local/ncs/modules/lib/canopennode ZEPHYR_CIVETWEB_MODULE_DIR=D:/Raffael/GitHub/P6_Software_local/ncs/modules/lib/civetweb ZEPHYR_FATFS_MODULE_DIR=D:/Raffael/GitHub/P6_Software_local/ncs/modules/fs/fatfs ZEPHYR_HAL_NORDIC_MODULE_DIR=D:/Raffael/GitHub/P6_Software_local/ncs/modules/hal/nordic ZEPHYR_HAL_NORDIC_KCONFIG=D:/Raffael/GitHub/P6_Software_local/ncs/zephyr/modules/hal_nordic/Kconfig ZEPHYR_ST_MODULE_DIR=D:/Raffael/GitHub/P6_Software_local/ncs/modules/hal/st ZEPHYR_LIBMETAL_MODULE_DIR=D:/Raffael/GitHub/P6_Software_local/ncs/modules/hal/libmetal ZEPHYR_LVGL_MODULE_DIR=D:/Raffael/GitHub/P6_Software_local/ncs/modules/lib/gui/lvgl ZEPHYR_MBEDTLS_MODULE_DIR=D:/Raffael/GitHub/P6_Software_local/ncs/modules/crypto/mbedtls ZEPHYR_MCUMGR_MODULE_DIR=D:/Raffael/GitHub/P6_Software_local/ncs/modules/lib/mcumgr ZEPHYR_OPEN_AMP_MODULE_DIR=D:/Raffael/GitHub/P6_Software_local/ncs/modules/lib/open-amp ZEPHYR_LORAMAC_NODE_MODULE_DIR=D:/Raffael/GitHub/P6_Software_local/ncs/modules/lib/loramac-node ZEPHYR_OPENTHREAD_MODULE_DIR=D:/Raffael/GitHub/P6_Software_local/ncs/modules/lib/openthread ZEPHYR_SEGGER_MODULE_DIR=D:/Raffael/GitHub/P6_Software_local/ncs/modules/debug/segger ZEPHYR_TINYCBOR_MODULE_DIR=D:/Raffael/GitHub/P6_Software_local/ncs/modules/lib/tinycbor ZEPHYR_TINYCRYPT_MODULE_DIR=D:/Raffael/GitHub/P6_Software_local/ncs/modules/crypto/tinycrypt ZEPHYR_LITTLEFS_MODULE_DIR=D:/Raffael/GitHub/P6_Software_local/ncs/modules/fs/littlefs ZEPHYR_MIPI_SYS_T_MODULE_DIR=D:/Raffael/GitHub/P6_Software_local/ncs/modules/debug/mipi-sys-t ZEPHYR_NRF_HW_MODELS_MODULE_DIR=D:/Raffael/GitHub/P6_Software_local/ncs/modules/bsim_hw_models/nrf_hw_models ZEPHYR_CONNECTEDHOMEIP_MODULE_DIR=D:/Raffael/GitHub/P6_Software_local/ncs/modules/lib/connectedhomeip EXTRA_DTC_FLAGS= DTS_POST_CPP=D:/Raffael/GitHub/P6_Software_local/my_projects/NRD/sht3xd_LoRa_Mesh_Sensor_Server_LPN_Dongle_v1_5_0/build/zephyr/nrf52840dk_nrf52840.dts.pre.tmp DTS_ROOT_BINDINGS=D:/Raffael/GitHub/P6_Software_local/ncs/nrf/dts/bindings?D:/Raffael/GitHub/P6_Software_local/ncs/zephyr/dts/bindings C:/Python38/python.exe D:/Raffael/GitHub/P6_Software_local/ncs/zephyr/scripts/kconfig/guiconfig.py D:/Raffael/GitHub/P6_Software_local/ncs/zephyr/Kconfig || (set FAIL_LINE=3& goto :ABORT)
goto :EOF

:ABORT
set ERROR_CODE=%ERRORLEVEL%
echo Batch file failed at line %FAIL_LINE% with errorcode %ERRORLEVEL%
exit /b %ERROR_CODE%