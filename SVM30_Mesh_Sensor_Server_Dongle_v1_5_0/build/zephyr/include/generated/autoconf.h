#define CONFIG_I2C 1
#define CONFIG_NET_CONFIG_IEEE802154_DEV_NAME ""
#define CONFIG_GPIO_NRF_P1 1
#define CONFIG_BT_HCI_VS_EXT 1
#define CONFIG_BOARD "nrf52840dongle_nrf52840"
#define CONFIG_FLASH_LOAD_OFFSET 0x1000
#define CONFIG_BT_CTLR 1
#define CONFIG_SOC "nRF52840_QIAA"
#define CONFIG_SOC_SERIES "nrf52"
#define CONFIG_NUM_IRQS 48
#define CONFIG_SYS_CLOCK_HW_CYCLES_PER_SEC 32768
#define CONFIG_HEAP_MEM_POOL_SIZE 0
#define CONFIG_GPIO 1
#define CONFIG_PM 1
#define CONFIG_HAS_POWER_STATE_DEEP_SLEEP_1 1
#define CONFIG_SOC_HAS_TIMING_FUNCTIONS 1
#define CONFIG_ARCH_HAS_CUSTOM_BUSY_WAIT 1
#define CONFIG_CLOCK_CONTROL 1
#define CONFIG_NRF_RTC_TIMER 1
#define CONFIG_SYS_CLOCK_TICKS_PER_SEC 32768
#define CONFIG_BUILD_OUTPUT_HEX 1
#define CONFIG_ROM_START_OFFSET 0x0
#define CONFIG_FLASH_SIZE 1024
#define CONFIG_FLASH_BASE_ADDRESS 0x0
#define CONFIG_TINYCRYPT 1
#define CONFIG_MAIN_STACK_SIZE 1024
#define CONFIG_PRIVILEGED_STACK_SIZE 1024
#define CONFIG_NCS_SAMPLES_DEFAULTS 1
#define CONFIG_LOG_DEFAULT_LEVEL 1
#define CONFIG_PM_PARTITION_SIZE_PROVISION 0x1000
#define CONFIG_PM_PARTITION_SIZE_B0_IMAGE 0x8000
#define CONFIG_SB_VALIDATION_INFO_MAGIC 0x86518483
#define CONFIG_SB_VALIDATION_POINTER_MAGIC 0x6919b47e
#define CONFIG_SB_VALIDATION_INFO_CRYPTO_ID 1
#define CONFIG_SB_VALIDATION_INFO_VERSION 2
#define CONFIG_SB_VALIDATION_METADATA_OFFSET 0
#define CONFIG_SB_VALIDATE_FW_SIGNATURE 1
#define CONFIG_BT_MAX_CONN 3
#define CONFIG_BT_HCI_TX_STACK_SIZE 640
#define CONFIG_BT_RX_STACK_SIZE 2048
#define CONFIG_SYSTEM_WORKQUEUE_STACK_SIZE 2048
#define CONFIG_BT_MESH_NRF_MODELS 1
#define CONFIG_BT_MESH_SENSOR_SRV 1
#define CONFIG_BT_MESH_SENSOR_SRV_SENSORS_MAX 4
#define CONFIG_BT_MESH_SENSOR_SRV_SETTINGS_MAX 8
#define CONFIG_BT_MESH_SENSOR 1
#define CONFIG_BT_MESH_SENSOR_CHANNELS_MAX 5
#define CONFIG_BT_MESH_SENSOR_CHANNEL_ENCODED_SIZE_MAX 4
#define CONFIG_BT_MESH_DK_PROV 1
#define CONFIG_BT_MESH_DK_PROV_OOB_BLINK 1
#define CONFIG_BT_MESH_DK_PROV_OOB_BUTTON 1
#define CONFIG_BT_MESH_DK_PROV_LOG_LEVEL_INF 1
#define CONFIG_BT_MESH_DK_PROV_LOG_LEVEL 3
#define CONFIG_MPSL_THREAD_COOP_PRIO 8
#define CONFIG_MPSL_SIGNAL_STACK_SIZE 1024
#define CONFIG_MPSL_TIMESLOT_SESSION_COUNT 0
#define CONFIG_MPSL_LOG_LEVEL_INF 1
#define CONFIG_MPSL_LOG_LEVEL 3
#define CONFIG_SRAM_SIZE 256
#define CONFIG_SRAM_BASE_ADDRESS 0x20000000
#define CONFIG_PM_PARTITION_SIZE_SETTINGS_STORAGE 0x2000
#define CONFIG_PM_SRAM_BASE 0x20000000
#define CONFIG_PM_SRAM_SIZE 0x40000
#define CONFIG_MGMT_FMFU_LOG_LEVEL_INF 1
#define CONFIG_MGMT_FMFU_LOG_LEVEL 3
#define CONFIG_BOOT_SIGNATURE_KEY_FILE ""
#define CONFIG_AGPS_LOG_LEVEL_INF 1
#define CONFIG_AGPS_LOG_LEVEL 3
#define CONFIG_NRF_ACL_FLASH_REGION_SIZE 0x1000
#define CONFIG_FPROTECT_BLOCK_SIZE 0x1000
#define CONFIG_DK_LIBRARY 1
#define CONFIG_DK_LIBRARY_BUTTON_SCAN_INTERVAL 10
#define CONFIG_DK_LIBRARY_INVERT_BUTTONS 1
#define CONFIG_DK_LIBRARY_INVERT_LEDS 1
#define CONFIG_DK_LIBRARY_DYNAMIC_BUTTON_HANDLERS 1
#define CONFIG_DK_LIBRARY_LOG_LEVEL_INF 1
#define CONFIG_DK_LIBRARY_LOG_LEVEL 3
#define CONFIG_RESET_ON_FATAL_ERROR 1
#define CONFIG_FATAL_ERROR_LOG_LEVEL_INF 1
#define CONFIG_FATAL_ERROR_LOG_LEVEL 3
#define CONFIG_ENTROPY_CC3XX 1
#define CONFIG_HW_CC3XX 1
#define CONFIG_HW_CC3XX_NAME "HW_CC3XX_0"
#define CONFIG_ZEPHYR_NRF_MODULE 1
#define CONFIG_DT_FLASH_WRITE_BLOCK_SIZE 4
#define CONFIG_ZEPHYR_MCUBOOT_MODULE 1
#define CONFIG_NRF_MODEM_SHMEM_CTRL_SIZE 0x4e8
#define CONFIG_NRFXLIB_CRYPTO 1
#define CONFIG_NRF_CC3XX_PLATFORM 1
#define CONFIG_CC3XX_MUTEX_LOCK 1
#define CONFIG_ZIGBEE_LIBRARY_PRODUCTION 1
#define CONFIG_ZEPHYR_NRFXLIB_MODULE 1
#define CONFIG_ZEPHYR_CDDL_GEN_MODULE 1
#define CONFIG_ZEPHYR_HAL_NORDIC_MODULE 1
#define CONFIG_HAS_NORDIC_DRIVERS 1
#define CONFIG_HAS_NRFX 1
#define CONFIG_NRFX_CLOCK 1
#define CONFIG_NRFX_CLOCK_LFXO_TWO_STAGE_ENABLED 1
#define CONFIG_NRFX_GPIOTE 1
#define CONFIG_NRFX_NVMC 1
#define CONFIG_NRFX_TWI 1
#define CONFIG_NRFX_TWI0 1
#define CONFIG_ZEPHYR_CONNECTEDHOMEIP_MODULE 1
#define CONFIG_HAS_CMSIS_CORE 1
#define CONFIG_HAS_CMSIS_CORE_M 1
#define CONFIG_NUM_PREEMPT_PRIORITIES 15
#define CONFIG_TINYCRYPT_ECC_DH 1
#define CONFIG_TINYCRYPT_AES 1
#define CONFIG_TINYCRYPT_AES_CMAC 1
#define CONFIG_BOARD_NRF52840DONGLE_NRF52840 1
#define CONFIG_BOARD_ENABLE_DCDC 1
#define CONFIG_BOARD_HAS_NRF5_BOOTLOADER 1
#define CONFIG_SOC_SERIES_NRF52X 1
#define CONFIG_CPU_HAS_ARM_MPU 1
#define CONFIG_SOC_FAMILY "nordic_nrf"
#define CONFIG_SOC_FAMILY_NRF 1
#define CONFIG_HAS_HW_NRF_ACL 1
#define CONFIG_HAS_HW_NRF_CC310 1
#define CONFIG_HAS_HW_NRF_CCM 1
#define CONFIG_HAS_HW_NRF_CCM_LFLEN_8BIT 1
#define CONFIG_HAS_HW_NRF_CLOCK 1
#define CONFIG_HAS_HW_NRF_COMP 1
#define CONFIG_HAS_HW_NRF_ECB 1
#define CONFIG_HAS_HW_NRF_EGU0 1
#define CONFIG_HAS_HW_NRF_EGU1 1
#define CONFIG_HAS_HW_NRF_EGU2 1
#define CONFIG_HAS_HW_NRF_EGU3 1
#define CONFIG_HAS_HW_NRF_EGU4 1
#define CONFIG_HAS_HW_NRF_EGU5 1
#define CONFIG_HAS_HW_NRF_GPIO0 1
#define CONFIG_HAS_HW_NRF_GPIO1 1
#define CONFIG_HAS_HW_NRF_GPIOTE 1
#define CONFIG_HAS_HW_NRF_I2S 1
#define CONFIG_HAS_HW_NRF_LPCOMP 1
#define CONFIG_HAS_HW_NRF_MWU 1
#define CONFIG_HAS_HW_NRF_NFCT 1
#define CONFIG_HAS_HW_NRF_NVMC_PE 1
#define CONFIG_HAS_HW_NRF_PDM 1
#define CONFIG_HAS_HW_NRF_POWER 1
#define CONFIG_HAS_HW_NRF_PPI 1
#define CONFIG_HAS_HW_NRF_PWM0 1
#define CONFIG_HAS_HW_NRF_PWM1 1
#define CONFIG_HAS_HW_NRF_PWM2 1
#define CONFIG_HAS_HW_NRF_PWM3 1
#define CONFIG_HAS_HW_NRF_QDEC 1
#define CONFIG_HAS_HW_NRF_QSPI 1
#define CONFIG_HAS_HW_NRF_RADIO_BLE_2M 1
#define CONFIG_HAS_HW_NRF_RADIO_TX_PWR_HIGH 1
#define CONFIG_HAS_HW_NRF_RADIO_BLE_CODED 1
#define CONFIG_HAS_HW_NRF_RADIO_IEEE802154 1
#define CONFIG_HAS_HW_NRF_RNG 1
#define CONFIG_HAS_HW_NRF_RTC0 1
#define CONFIG_HAS_HW_NRF_RTC1 1
#define CONFIG_HAS_HW_NRF_RTC2 1
#define CONFIG_HAS_HW_NRF_SAADC 1
#define CONFIG_HAS_HW_NRF_SPI0 1
#define CONFIG_HAS_HW_NRF_SPI1 1
#define CONFIG_HAS_HW_NRF_SPI2 1
#define CONFIG_HAS_HW_NRF_SPIM0 1
#define CONFIG_HAS_HW_NRF_SPIM1 1
#define CONFIG_HAS_HW_NRF_SPIM2 1
#define CONFIG_HAS_HW_NRF_SPIM3 1
#define CONFIG_HAS_HW_NRF_SPIS0 1
#define CONFIG_HAS_HW_NRF_SPIS1 1
#define CONFIG_HAS_HW_NRF_SPIS2 1
#define CONFIG_HAS_HW_NRF_SWI0 1
#define CONFIG_HAS_HW_NRF_SWI1 1
#define CONFIG_HAS_HW_NRF_SWI2 1
#define CONFIG_HAS_HW_NRF_SWI3 1
#define CONFIG_HAS_HW_NRF_SWI4 1
#define CONFIG_HAS_HW_NRF_SWI5 1
#define CONFIG_HAS_HW_NRF_TEMP 1
#define CONFIG_HAS_HW_NRF_TIMER0 1
#define CONFIG_HAS_HW_NRF_TIMER1 1
#define CONFIG_HAS_HW_NRF_TIMER2 1
#define CONFIG_HAS_HW_NRF_TIMER3 1
#define CONFIG_HAS_HW_NRF_TIMER4 1
#define CONFIG_HAS_HW_NRF_TWI0 1
#define CONFIG_HAS_HW_NRF_TWI1 1
#define CONFIG_HAS_HW_NRF_TWIM0 1
#define CONFIG_HAS_HW_NRF_TWIM1 1
#define CONFIG_HAS_HW_NRF_TWIS0 1
#define CONFIG_HAS_HW_NRF_TWIS1 1
#define CONFIG_HAS_HW_NRF_UART0 1
#define CONFIG_HAS_HW_NRF_UARTE0 1
#define CONFIG_HAS_HW_NRF_UARTE1 1
#define CONFIG_HAS_HW_NRF_USBD 1
#define CONFIG_HAS_HW_NRF_WDT 1
#define CONFIG_NRF_HW_TIMER0_RESERVED 1
#define CONFIG_NRF_HW_RTC0_RESERVED 1
#define CONFIG_NRF_HW_RTC1_RESERVED 1
#define CONFIG_SOC_NRF52840 1
#define CONFIG_SOC_NRF52840_QIAA 1
#define CONFIG_SOC_DCDC_NRF52X 1
#define CONFIG_NFCT_PINS_AS_GPIOS 1
#define CONFIG_GPIO_AS_PINRESET 1
#define CONFIG_NRF_ENABLE_ICACHE 1
#define CONFIG_SOC_LOG_LEVEL_INF 1
#define CONFIG_SOC_LOG_LEVEL 3
#define CONFIG_SOC_COMPATIBLE_NRF 1
#define CONFIG_SOC_COMPATIBLE_NRF52X 1
#define CONFIG_ARCH "arm"
#define CONFIG_CPU_CORTEX 1
#define CONFIG_CPU_CORTEX_M 1
#define CONFIG_ISA_THUMB2 1
#define CONFIG_ASSEMBLER_ISA_THUMB2 1
#define CONFIG_COMPILER_ISA_THUMB2 1
#define CONFIG_STACK_ALIGN_DOUBLE_WORD 1
#define CONFIG_PLATFORM_SPECIFIC_INIT 1
#define CONFIG_FAULT_DUMP 2
#define CONFIG_ARM_STACK_PROTECTION 1
#define CONFIG_CPU_CORTEX_M4 1
#define CONFIG_CPU_CORTEX_M_HAS_SYSTICK 1
#define CONFIG_CPU_CORTEX_M_HAS_DWT 1
#define CONFIG_CPU_CORTEX_M_HAS_BASEPRI 1
#define CONFIG_CPU_CORTEX_M_HAS_VTOR 1
#define CONFIG_CPU_CORTEX_M_HAS_PROGRAMMABLE_FAULT_PRIOS 1
#define CONFIG_ARMV7_M_ARMV8_M_MAINLINE 1
#define CONFIG_ARMV7_M_ARMV8_M_FP 1
#define CONFIG_GEN_ISR_TABLES 1
#define CONFIG_ARM_MPU 1
#define CONFIG_ARM_MPU_REGION_MIN_ALIGN_AND_SIZE 32
#define CONFIG_MPU_STACK_GUARD 1
#define CONFIG_MPU_ALLOW_FLASH_WRITE 1
#define CONFIG_CUSTOM_SECTION_MIN_ALIGN_SIZE 32
#define CONFIG_GEN_IRQ_VECTOR_TABLE 1
#define CONFIG_IDLE_STACK_SIZE 320
#define CONFIG_ISR_STACK_SIZE 2048
#define CONFIG_TEST_EXTRA_STACKSIZE 0
#define CONFIG_ARM 1
#define CONFIG_ARCH_IS_SET 1
#define CONFIG_ARCH_LOG_LEVEL_INF 1
#define CONFIG_ARCH_LOG_LEVEL 3
#define CONFIG_MPU_LOG_LEVEL_INF 1
#define CONFIG_MPU_LOG_LEVEL 3
#define CONFIG_HW_STACK_PROTECTION 1
#define CONFIG_KOBJECT_TEXT_AREA 256
#define CONFIG_GEN_PRIV_STACKS 1
#define CONFIG_GEN_SW_ISR_TABLE 1
#define CONFIG_ARCH_SW_ISR_TABLE_ALIGN 0
#define CONFIG_GEN_IRQ_START_VECTOR 0
#define CONFIG_ARCH_HAS_TIMING_FUNCTIONS 1
#define CONFIG_ARCH_HAS_STACK_PROTECTION 1
#define CONFIG_ARCH_HAS_USERSPACE 1
#define CONFIG_ARCH_HAS_EXECUTABLE_PAGE_BIT 1
#define CONFIG_ARCH_HAS_RAMFUNC_SUPPORT 1
#define CONFIG_ARCH_HAS_NESTED_EXCEPTION_DETECTION 1
#define CONFIG_ARCH_SUPPORTS_COREDUMP 1
#define CONFIG_ARCH_SUPPORTS_ARCH_HW_INIT 1
#define CONFIG_ARCH_HAS_EXTRA_EXCEPTION_INFO 1
#define CONFIG_ARCH_HAS_THREAD_LOCAL_STORAGE 1
#define CONFIG_ARCH_HAS_THREAD_ABORT 1
#define CONFIG_CPU_HAS_FPU 1
#define CONFIG_CPU_HAS_MPU 1
#define CONFIG_MPU 1
#define CONFIG_MPU_REQUIRES_POWER_OF_TWO_ALIGNMENT 1
#define CONFIG_SRAM_REGION_PERMISSIONS 1
#define CONFIG_KERNEL_LOG_LEVEL_INF 1
#define CONFIG_KERNEL_LOG_LEVEL 3
#define CONFIG_MULTITHREADING 1
#define CONFIG_NUM_COOP_PRIORITIES 16
#define CONFIG_MAIN_THREAD_PRIORITY 0
#define CONFIG_COOP_ENABLED 1
#define CONFIG_PREEMPT_ENABLED 1
#define CONFIG_PRIORITY_CEILING 0
#define CONFIG_NUM_METAIRQ_PRIORITIES 0
#define CONFIG_THREAD_STACK_INFO 1
#define CONFIG_ERRNO 1
#define CONFIG_SCHED_DUMB 1
#define CONFIG_WAITQ_DUMB 1
#define CONFIG_BOOT_DELAY 0
#define CONFIG_SYSTEM_WORKQUEUE_PRIORITY -1
#define CONFIG_ATOMIC_OPERATIONS_BUILTIN 1
#define CONFIG_TIMESLICING 1
#define CONFIG_TIMESLICE_SIZE 0
#define CONFIG_TIMESLICE_PRIORITY 0
#define CONFIG_POLL 1
#define CONFIG_NUM_MBOX_ASYNC_MSGS 10
#define CONFIG_NUM_PIPE_ASYNC_MSGS 10
#define CONFIG_KERNEL_MEM_POOL 1
#define CONFIG_ARCH_HAS_CUSTOM_SWAP_TO_MAIN 1
#define CONFIG_SWAP_NONATOMIC 1
#define CONFIG_SYS_CLOCK_EXISTS 1
#define CONFIG_TIMEOUT_64BIT 1
#define CONFIG_XIP 1
#define CONFIG_KERNEL_INIT_PRIORITY_OBJECTS 30
#define CONFIG_KERNEL_INIT_PRIORITY_DEFAULT 40
#define CONFIG_KERNEL_INIT_PRIORITY_DEVICE 50
#define CONFIG_APPLICATION_INIT_PRIORITY 90
#define CONFIG_STACK_POINTER_RANDOM 0
#define CONFIG_MP_NUM_CPUS 1
#define CONFIG_TICKLESS_IDLE 1
#define CONFIG_TICKLESS_IDLE_THRESH 3
#define CONFIG_TICKLESS_KERNEL 1
#define CONFIG_HAS_DTS 1
#define CONFIG_HAS_DTS_GPIO 1
#define CONFIG_CONSOLE 1
#define CONFIG_CONSOLE_INPUT_MAX_LINE_LEN 128
#define CONFIG_UART_CONSOLE_LOG_LEVEL_INF 1
#define CONFIG_UART_CONSOLE_LOG_LEVEL 3
#define CONFIG_HAS_SEGGER_RTT 1
#define CONFIG_NRF_RTC_TIMER_USER_CHAN_COUNT 0
#define CONFIG_SYSTEM_CLOCK_WAIT_FOR_STABILITY 1
#define CONFIG_SYSTEM_CLOCK_DISABLE 1
#define CONFIG_SYSTEM_CLOCK_INIT_PRIORITY 0
#define CONFIG_TICKLESS_CAPABLE 1
#define CONFIG_ENTROPY_GENERATOR 1
#define CONFIG_ENTROPY_NRF5_RNG 1
#define CONFIG_ENTROPY_NRF5_BIAS_CORRECTION 1
#define CONFIG_ENTROPY_NRF5_THR_POOL_SIZE 8
#define CONFIG_ENTROPY_NRF5_THR_THRESHOLD 4
#define CONFIG_ENTROPY_NRF5_ISR_POOL_SIZE 16
#define CONFIG_ENTROPY_NRF5_ISR_THRESHOLD 12
#define CONFIG_ENTROPY_HAS_DRIVER 1
#define CONFIG_GPIO_LOG_LEVEL_INF 1
#define CONFIG_GPIO_LOG_LEVEL 3
#define CONFIG_GPIO_NRFX 1
#define CONFIG_GPIO_NRF_INIT_PRIORITY 40
#define CONFIG_GPIO_NRF_P0 1
#define CONFIG_I2C_NRFX 1
#define CONFIG_I2C_0_NRF_TWI 1
#define CONFIG_I2C_INIT_PRIORITY 60
#define CONFIG_I2C_LOG_LEVEL_INF 1
#define CONFIG_I2C_LOG_LEVEL 3
#define CONFIG_CLOCK_CONTROL_LOG_LEVEL_INF 1
#define CONFIG_CLOCK_CONTROL_LOG_LEVEL 3
#define CONFIG_CLOCK_CONTROL_NRF 1
#define CONFIG_CLOCK_CONTROL_NRF_K32SRC_XTAL 1
#define CONFIG_CLOCK_CONTROL_NRF_K32SRC_20PPM 1
#define CONFIG_CLOCK_CONTROL_NRF_ACCURACY 20
#define CONFIG_FLASH_HAS_DRIVER_ENABLED 1
#define CONFIG_FLASH_HAS_PAGE_LAYOUT 1
#define CONFIG_FLASH 1
#define CONFIG_FLASH_LOG_LEVEL_INF 1
#define CONFIG_FLASH_LOG_LEVEL 3
#define CONFIG_FLASH_PAGE_LAYOUT 1
#define CONFIG_SOC_FLASH_NRF 1
#define CONFIG_SOC_FLASH_NRF_RADIO_SYNC_TICKER 1
#define CONFIG_HWINFO 1
#define CONFIG_HWINFO_HAS_DRIVER 1
#define CONFIG_HWINFO_NRF 1
#define CONFIG_NEWLIB_LIBC 1
#define CONFIG_HAS_NEWLIB_LIBC_NANO 1
#define CONFIG_NEWLIB_LIBC_NANO 1
#define CONFIG_NEWLIB_LIBC_FLOAT_PRINTF 1
#define CONFIG_SYS_HEAP_ALLOC_LOOPS 3
#define CONFIG_CBPRINTF_COMPLETE 1
#define CONFIG_CBPRINTF_FULL_INTEGRAL 1
#define CONFIG_CBPRINTF_N_SPECIFIER 1
#define CONFIG_POSIX_MAX_FDS 4
#define CONFIG_MAX_TIMER_COUNT 5
#define CONFIG_BT 1
#define CONFIG_BT_LOG_LEVEL_INF 1
#define CONFIG_BT_LOG_LEVEL 3
#define CONFIG_BT_HCI 1
#define CONFIG_BT_PERIPHERAL 1
#define CONFIG_BT_BROADCASTER 1
#define CONFIG_BT_OBSERVER 1
#define CONFIG_BT_CONN 1
#define CONFIG_BT_HAS_HCI_VS 1
#define CONFIG_BT_HCI_VS 1
#define CONFIG_BT_ASSERT 1
#define CONFIG_BT_ASSERT_VERBOSE 1
#define CONFIG_BT_DEBUG_NONE 1
#define CONFIG_BT_HCI_HOST 1
#define CONFIG_BT_HCI_CMD_COUNT 2
#define CONFIG_BT_RX_BUF_COUNT 3
#define CONFIG_BT_RX_BUF_LEN 77
#define CONFIG_BT_DISCARDABLE_BUF_COUNT 20
#define CONFIG_BT_DISCARDABLE_BUF_SIZE 45
#define CONFIG_BT_HCI_ECC_STACK_SIZE 1100
#define CONFIG_BT_HCI_TX_PRIO 7
#define CONFIG_BT_HCI_RESERVE 0
#define CONFIG_BT_RECV_IS_RX_THREAD 1
#define CONFIG_BT_RX_PRIO 8
#define CONFIG_BT_DRIVER_RX_HIGH_PRIO 6
#define CONFIG_BT_SETTINGS 1
#define CONFIG_BT_SETTINGS_CCC_LAZY_LOADING 1
#define CONFIG_BT_SETTINGS_USE_PRINTK 1
#define CONFIG_BT_CONN_TX_MAX 8
#define CONFIG_BT_L2CAP_RX_MTU 69
#define CONFIG_BT_L2CAP_TX_BUF_COUNT 8
#define CONFIG_BT_L2CAP_TX_FRAG_COUNT 2
#define CONFIG_BT_L2CAP_TX_MTU 69
#define CONFIG_BT_ATT_ENFORCE_FLOW 1
#define CONFIG_BT_ATT_PREPARE_COUNT 0
#define CONFIG_BT_ATT_TX_MAX 8
#define CONFIG_BT_GATT_SERVICE_CHANGED 1
#define CONFIG_BT_GATT_DYNAMIC_DB 1
#define CONFIG_BT_GATT_CACHING 1
#define CONFIG_BT_GATT_READ_MULTIPLE 1
#define CONFIG_BT_GAP_AUTO_UPDATE_CONN_PARAMS 1
#define CONFIG_BT_GAP_PERIPHERAL_PREF_PARAMS 1
#define CONFIG_BT_PERIPHERAL_PREF_MIN_INT 24
#define CONFIG_BT_PERIPHERAL_PREF_MAX_INT 40
#define CONFIG_BT_PERIPHERAL_PREF_SLAVE_LATENCY 0
#define CONFIG_BT_PERIPHERAL_PREF_TIMEOUT 42
#define CONFIG_BT_MAX_PAIRED 0
#define CONFIG_BT_CREATE_CONN_TIMEOUT 3
#define CONFIG_BT_CONN_PARAM_UPDATE_TIMEOUT 5000
#define CONFIG_BT_BACKGROUND_SCAN_INTERVAL 2048
#define CONFIG_BT_BACKGROUND_SCAN_WINDOW 18
#define CONFIG_BT_DEVICE_NAME "CO2 VOC TEMP HUM Sensor"
#define CONFIG_BT_DEVICE_APPEARANCE 0
#define CONFIG_BT_ID_MAX 1
#define CONFIG_BT_ECC 1
#define CONFIG_BT_TINYCRYPT_ECC 1
#define CONFIG_BT_HOST_CCM 1
#define CONFIG_BT_CTLR_LE_ENC_SUPPORT 1
#define CONFIG_BT_CTLR_CONN_PARAM_REQ_SUPPORT 1
#define CONFIG_BT_CTLR_EXT_REJ_IND_SUPPORT 1
#define CONFIG_BT_CTLR_SLAVE_FEAT_REQ_SUPPORT 1
#define CONFIG_BT_CTLR_DATA_LEN_UPDATE_SUPPORT 1
#define CONFIG_BT_CTLR_PRIVACY_SUPPORT 1
#define CONFIG_BT_CTLR_EXT_SCAN_FP_SUPPORT 1
#define CONFIG_BT_CTLR_PHY_UPDATE_SUPPORT 1
#define CONFIG_BT_CTLR_PHY_2M_SUPPORT 1
#define CONFIG_BT_CTLR_PHY_CODED_SUPPORT 1
#define CONFIG_BT_CTLR_ADV_EXT_SUPPORT 1
#define CONFIG_BT_CTLR_ADV_PERIODIC_SUPPORT 1
#define CONFIG_BT_CTLR_SYNC_PERIODIC_SUPPORT 1
#define CONFIG_BT_CTLR_ADV_ISO_SUPPORT 1
#define CONFIG_BT_CTLR_SYNC_ISO_SUPPORT 1
#define CONFIG_BT_CTLR_CHAN_SEL_2_SUPPORT 1
#define CONFIG_BT_CTLR_MIN_USED_CHAN_SUPPORT 1
#define CONFIG_BT_CTLR_DTM_HCI_SUPPORT 1
#define CONFIG_BT_CTLR_CONN_RSSI_SUPPORT 1
#define CONFIG_BT_LL_SW_SPLIT 1
#define CONFIG_BT_CTLR_CRYPTO 1
#define CONFIG_BT_CTLR_HCI_VS_BUILD_INFO ""
#define CONFIG_BT_CTLR_DUP_FILTER_LEN 0
#define CONFIG_BT_CTLR_RX_BUFFERS 1
#define CONFIG_BT_CTLR_TX_BUFFERS 3
#define CONFIG_BT_CTLR_TX_BUFFER_SIZE 27
#define CONFIG_BT_CTLR_ISO_TX_BUFFER_SIZE 27
#define CONFIG_BT_CTLR_TX_PWR_0 1
#define CONFIG_BT_CTLR_CONN_PARAM_REQ 1
#define CONFIG_BT_CTLR_EXT_REJ_IND 1
#define CONFIG_BT_CTLR_SLAVE_FEAT_REQ 1
#define CONFIG_BT_CTLR_FILTER 1
#define CONFIG_BT_CTLR_WL_SIZE 8
#define CONFIG_BT_CTLR_EXT_SCAN_FP 1
#define CONFIG_BT_LLL_VENDOR_NORDIC 1
#define CONFIG_BT_CTLR_XTAL_ADVANCED_SUPPORT 1
#define CONFIG_BT_CTLR_SCHED_ADVANCED_SUPPORT 1
#define CONFIG_BT_CTLR_TIFS_HW_SUPPORT 1
#define CONFIG_BT_CTLR_RX_PRIO_STACK_SIZE 448
#define CONFIG_BT_CTLR_COMPANY_ID 0x0059
#define CONFIG_BT_CTLR_SUBVERSION_NUMBER 0xFFFF
#define CONFIG_BT_CTLR_ADV_DATA_BUF_MAX 1
#define CONFIG_BT_CTLR_XTAL_ADVANCED 1
#define CONFIG_BT_CTLR_XTAL_THRESHOLD 1500
#define CONFIG_BT_CTLR_LLL_PRIO 0
#define CONFIG_BT_CTLR_ULL_HIGH_PRIO 0
#define CONFIG_BT_CTLR_ULL_LOW_PRIO 0
#define CONFIG_BT_CTLR_RADIO_ENABLE_FAST 1
#define CONFIG_BT_CTLR_LLCP_CONN 3
#define CONFIG_BT_CTLR_FORCE_MD_COUNT 0
#define CONFIG_BT_CTLR_CONN_RANDOM_FORCE 1
#define CONFIG_BT_CTLR_SCAN_UNRESERVED 1
#define CONFIG_BT_MAYFLY_YIELD_AFTER_CALL 1
#define CONFIG_BT_TICKER_EXT 1
#define CONFIG_BT_COMPANY_ID 0x0059
#define CONFIG_BT_MESH 1
#define CONFIG_BT_MESH_PROV 1
#define CONFIG_BT_MESH_PROV_DEVICE 1
#define CONFIG_BT_MESH_PB_ADV 1
#define CONFIG_BT_MESH_UNPROV_BEACON_INT 5
#define CONFIG_BT_MESH_PB_ADV_RETRANS_TIMEOUT 500
#define CONFIG_BT_MESH_PROXY 1
#define CONFIG_BT_MESH_PB_GATT 1
#define CONFIG_BT_MESH_GATT_PROXY 1
#define CONFIG_BT_MESH_GATT_PROXY_ENABLED 1
#define CONFIG_BT_MESH_NODE_ID_TIMEOUT 60
#define CONFIG_BT_MESH_PROXY_FILTER_SIZE 3
#define CONFIG_BT_MESH_SUBNET_COUNT 1
#define CONFIG_BT_MESH_APP_KEY_COUNT 1
#define CONFIG_BT_MESH_MODEL_KEY_COUNT 1
#define CONFIG_BT_MESH_MODEL_GROUP_COUNT 1
#define CONFIG_BT_MESH_LABEL_COUNT 1
#define CONFIG_BT_MESH_CRPL 10
#define CONFIG_BT_MESH_MSG_CACHE_SIZE 10
#define CONFIG_BT_MESH_ADV_BUF_COUNT 13
#define CONFIG_BT_MESH_ADV_LEGACY 1
#define CONFIG_BT_MESH_ADV_STACK_SIZE 768
#define CONFIG_BT_MESH_IVU_DIVIDER 4
#define CONFIG_BT_MESH_TX_SEG_MSG_COUNT 1
#define CONFIG_BT_MESH_RX_SEG_MSG_COUNT 1
#define CONFIG_BT_MESH_SEG_BUFS 64
#define CONFIG_BT_MESH_RX_SEG_MAX 3
#define CONFIG_BT_MESH_TX_SEG_MAX 10
#define CONFIG_BT_MESH_DEFAULT_TTL 7
#define CONFIG_BT_MESH_LOOPBACK_BUFS 3
#define CONFIG_BT_MESH_TX_SEG_RETRANS_COUNT 4
#define CONFIG_BT_MESH_TX_SEG_RETRANS_TIMEOUT_UNICAST 400
#define CONFIG_BT_MESH_TX_SEG_RETRANS_TIMEOUT_GROUP 50
#define CONFIG_BT_MESH_NETWORK_TRANSMIT_COUNT 2
#define CONFIG_BT_MESH_NETWORK_TRANSMIT_INTERVAL 20
#define CONFIG_BT_MESH_RELAY 1
#define CONFIG_BT_MESH_RELAY_ENABLED 1
#define CONFIG_BT_MESH_RELAY_RETRANSMIT_COUNT 2
#define CONFIG_BT_MESH_RELAY_RETRANSMIT_INTERVAL 20
#define CONFIG_BT_MESH_BEACON_ENABLED 1
#define CONFIG_BT_MESH_FRIEND 1
#define CONFIG_BT_MESH_FRIEND_ENABLED 1
#define CONFIG_BT_MESH_FRIEND_RECV_WIN 255
#define CONFIG_BT_MESH_FRIEND_QUEUE_SIZE 16
#define CONFIG_BT_MESH_FRIEND_SUB_LIST_SIZE 3
#define CONFIG_BT_MESH_FRIEND_LPN_COUNT 2
#define CONFIG_BT_MESH_FRIEND_SEG_RX 1
#define CONFIG_BT_MESH_STORE_TIMEOUT 2
#define CONFIG_BT_MESH_SEQ_STORE_RATE 128
#define CONFIG_BT_MESH_RPL_STORE_TIMEOUT 5
#define CONFIG_PRINTK 1
#define CONFIG_ASSERT 1
#define CONFIG_ASSERT_LEVEL 2
#define CONFIG_SPIN_VALIDATE 1
#define CONFIG_ASSERT_VERBOSE 1
#define CONFIG_ASSERT_NO_COND_INFO 1
#define CONFIG_ASSERT_NO_MSG_INFO 1
#define CONFIG_NVS 1
#define CONFIG_NVS_LOG_LEVEL_INF 1
#define CONFIG_NVS_LOG_LEVEL 3
#define CONFIG_LOG 1
#define CONFIG_LOG_MINIMAL 1
#define CONFIG_LOG_OVERRIDE_LEVEL 0
#define CONFIG_LOG_MAX_LEVEL 4
#define CONFIG_NET_BUF 1
#define CONFIG_NET_BUF_USER_DATA_SIZE 4
#define CONFIG_NET_BUF_LOG_LEVEL_INF 1
#define CONFIG_NET_BUF_LOG_LEVEL 3
#define CONFIG_PM_POLICY_RESIDENCY 1
#define CONFIG_PM_POLICY_RESIDENCY_DEFAULT 1
#define CONFIG_PM_MIN_RESIDENCY_DEEP_SLEEP_1 60000
#define CONFIG_PM_LOG_LEVEL_INF 1
#define CONFIG_PM_LOG_LEVEL 3
#define CONFIG_ENTROPY_DEVICE_RANDOM_GENERATOR 1
#define CONFIG_CSPRING_ENABLED 1
#define CONFIG_HARDWARE_DEVICE_CS_GENERATOR 1
#define CONFIG_FLASH_MAP 1
#define CONFIG_SETTINGS 1
#define CONFIG_SETTINGS_LOG_LEVEL_INF 1
#define CONFIG_SETTINGS_LOG_LEVEL 3
#define CONFIG_SETTINGS_DYNAMIC_HANDLERS 1
#define CONFIG_SETTINGS_NVS 1
#define CONFIG_SETTINGS_NVS_SECTOR_SIZE_MULT 1
#define CONFIG_SETTINGS_NVS_SECTOR_COUNT 8
#define CONFIG_TEST_ARM_CORTEX_M 1
#define CONFIG_TOOLCHAIN_GNUARMEMB 1
#define CONFIG_LINKER_ORPHAN_SECTION_WARN 1
#define CONFIG_HAS_FLASH_LOAD_OFFSET 1
#define CONFIG_FLASH_LOAD_SIZE 0x0
#define CONFIG_KERNEL_ENTRY "__start"
#define CONFIG_LINKER_SORT_BY_ALIGNMENT 1
#define CONFIG_SIZE_OPTIMIZATIONS 1
#define CONFIG_COMPILER_OPT ""
#define CONFIG_RUNTIME_ERROR_CHECKS 1
#define CONFIG_KERNEL_BIN_NAME "zephyr"
#define CONFIG_OUTPUT_STAT 1
#define CONFIG_OUTPUT_DISASSEMBLY 1
#define CONFIG_OUTPUT_PRINT_MEMORY_USAGE 1
#define CONFIG_BUILD_OUTPUT_BIN 1
#define CONFIG_REBOOT 1
#define CONFIG_COMPAT_INCLUDES 1
