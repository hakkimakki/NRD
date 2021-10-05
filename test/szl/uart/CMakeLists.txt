if(CONFIG_SZL_UART_ENABLE)
	target_sources(app PRIVATE szl_uart.c)
	target_include_directories(app PRIVATE ./)
endif()