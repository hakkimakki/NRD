@echo off
cd /D C:\Users\raffa\Github\NRD\LightSwitch_RemoteControl_v1_8_0\build_2\zephyr\kconfig || (set FAIL_LINE=2& goto :ABORT)
"C:\Program Files\CMake\bin\cmake.exe" -E env ZEPHYR_BASE=C:/Users/raffa/Github/ncs/zephyr ZEPHYR_TOOLCHAIN_VARIANT=gnuarmemb PYTHON_EXECUTABLE=C:/Python37/python.exe srctree=C:/Users/raffa/Github/ncs/zephyr KERNELVERSION=0x2070000 KCONFIG_CONFIG=C:/Users/raffa/Github/NRD/LightSwitch_RemoteControl_v1_8_0/build_2/zephyr/.config ARCH=arm ARCH_DIR=C:/Users/raffa/Github/ncs/zephyr/arch BOARD_DIR=C:/Users/raffa/Github/ncs/zephyr/boards/arm/nrf52840dongle_nrf52840 KCONFIG_BINARY_DIR=C:/Users/raffa/Github/NRD/LightSwitch_RemoteControl_v1_8_0/build_2/Kconfig TOOLCHAIN_KCONFIG_DIR=C:/Users/raffa/Github/ncs/zephyr/cmake/toolchain/gnuarmemb TOOLCHAIN_HAS_NEWLIB=y EDT_PICKLE=C:/Users/raffa/Github/NRD/LightSwitch_RemoteControl_v1_8_0/build_2/zephyr/edt.pickle ZEPHYR_NRF_MODULE_DIR=C:/Users/raffa/Github/ncs/nrf ZEPHYR_MCUBOOT_MODULE_DIR=C:/Users/raffa/Github/ncs/bootloader/mcuboot ZEPHYR_MCUBOOT_KCONFIG=C:/Users/raffa/Github/ncs/nrf/modules/mcuboot/Kconfig ZEPHYR_TRUSTED_FIRMWARE_M_MODULE_DIR=C:/Users/raffa/Github/ncs/modules/tee/tfm ZEPHYR_TRUSTED_FIRMWARE_M_KCONFIG=C:/Users/raffa/Github/ncs/nrf/modules/trusted-firmware-m/Kconfig ZEPHYR_TFM_MCUBOOT_MODULE_DIR=C:/Users/raffa/Github/ncs/modules/tee/tfm-mcuboot ZEPHYR_CJSON_MODULE_DIR=C:/Users/raffa/Github/ncs/modules/lib/cjson ZEPHYR_CJSON_KCONFIG=C:/Users/raffa/Github/ncs/nrf/modules/cjson/Kconfig ZEPHYR_PELION_DM_MODULE_DIR=C:/Users/raffa/Github/ncs/modules/lib/pelion-dm ZEPHYR_CDDL_GEN_MODULE_DIR=C:/Users/raffa/Github/ncs/modules/lib/cddl-gen ZEPHYR_CDDL_GEN_KCONFIG=C:/Users/raffa/Github/ncs/nrf/modules/cddl-gen/Kconfig ZEPHYR_MEMFAULT_FIRMWARE_SDK_MODULE_DIR=C:/Users/raffa/Github/ncs/modules/lib/memfault-firmware-sdk ZEPHYR_CANOPENNODE_MODULE_DIR=C:/Users/raffa/Github/ncs/modules/lib/canopennode ZEPHYR_CANOPENNODE_KCONFIG=C:/Users/raffa/Github/ncs/zephyr/modules/canopennode/Kconfig ZEPHYR_CIVETWEB_MODULE_DIR=C:/Users/raffa/Github/ncs/modules/lib/civetweb ZEPHYR_CMSIS_MODULE_DIR=C:/Users/raffa/Github/ncs/modules/hal/cmsis ZEPHYR_FATFS_MODULE_DIR=C:/Users/raffa/Github/ncs/modules/fs/fatfs ZEPHYR_HAL_NORDIC_MODULE_DIR=C:/Users/raffa/Github/ncs/modules/hal/nordic ZEPHYR_HAL_NORDIC_KCONFIG=C:/Users/raffa/Github/ncs/zephyr/modules/hal_nordic/Kconfig ZEPHYR_ST_MODULE_DIR=C:/Users/raffa/Github/ncs/modules/hal/st ZEPHYR_LIBMETAL_MODULE_DIR=C:/Users/raffa/Github/ncs/modules/hal/libmetal ZEPHYR_LITTLEFS_MODULE_DIR=C:/Users/raffa/Github/ncs/modules/fs/littlefs ZEPHYR_LORAMAC_NODE_MODULE_DIR=C:/Users/raffa/Github/ncs/modules/lib/loramac-node ZEPHYR_LORAMAC_NODE_KCONFIG=C:/Users/raffa/Github/ncs/zephyr/modules/loramac-node/Kconfig ZEPHYR_LVGL_MODULE_DIR=C:/Users/raffa/Github/ncs/modules/lib/gui/lvgl ZEPHYR_LZ4_MODULE_DIR=C:/Users/raffa/Github/ncs/modules/lib/lz4 ZEPHYR_LZ4_KCONFIG=C:/Users/raffa/Github/ncs/zephyr/modules/lz4/Kconfig ZEPHYR_MBEDTLS_MODULE_DIR=C:/Users/raffa/Github/ncs/modules/crypto/mbedtls ZEPHYR_MBEDTLS_KCONFIG=C:/Users/raffa/Github/ncs/zephyr/modules/mbedtls/Kconfig ZEPHYR_MCUMGR_MODULE_DIR=C:/Users/raffa/Github/ncs/modules/lib/mcumgr ZEPHYR_MIPI_SYS_T_MODULE_DIR=C:/Users/raffa/Github/ncs/modules/debug/mipi-sys-t ZEPHYR_NANOPB_MODULE_DIR=C:/Users/raffa/Github/ncs/modules/lib/nanopb ZEPHYR_NANOPB_KCONFIG=C:/Users/raffa/Github/ncs/zephyr/modules/nanopb/Kconfig ZEPHYR_NRF_HW_MODELS_MODULE_DIR=C:/Users/raffa/Github/ncs/modules/bsim_hw_models/nrf_hw_models ZEPHYR_OPEN_AMP_MODULE_DIR=C:/Users/raffa/Github/ncs/modules/lib/open-amp ZEPHYR_OPENTHREAD_MODULE_DIR=C:/Users/raffa/Github/ncs/modules/lib/openthread ZEPHYR_SEGGER_MODULE_DIR=C:/Users/raffa/Github/ncs/modules/debug/segger ZEPHYR_TINYCBOR_MODULE_DIR=C:/Users/raffa/Github/ncs/modules/lib/tinycbor ZEPHYR_TINYCRYPT_MODULE_DIR=C:/Users/raffa/Github/ncs/modules/crypto/tinycrypt ZEPHYR_TRACERECORDER_MODULE_DIR=C:/Users/raffa/Github/ncs/modules/debug/TraceRecorder ZEPHYR_TRACERECORDER_KCONFIG=C:/Users/raffa/Github/ncs/zephyr/modules/TraceRecorder/Kconfig ZEPHYR_NRFXLIB_MODULE_DIR=C:/Users/raffa/Github/ncs/nrfxlib ZEPHYR_CONNECTEDHOMEIP_MODULE_DIR=C:/Users/raffa/Github/ncs/modules/lib/matter SHIELD_AS_LIST= DTS_POST_CPP=C:/Users/raffa/Github/NRD/LightSwitch_RemoteControl_v1_8_0/build_2/zephyr/nrf52840dongle_nrf52840.dts.pre.tmp DTS_ROOT_BINDINGS=C:/Users/raffa/Github/ncs/nrf/dts/bindings?C:/Users/raffa/Github/ncs/zephyr/dts/bindings C:/Python37/python.exe C:/Users/raffa/Github/ncs/zephyr/scripts/kconfig/menuconfig.py C:/Users/raffa/Github/ncs/zephyr/Kconfig || (set FAIL_LINE=3& goto :ABORT)
goto :EOF

:ABORT
set ERROR_CODE=%ERRORLEVEL%
echo Batch file failed at line %FAIL_LINE% with errorcode %ERRORLEVEL%
exit /b %ERROR_CODE%