if(CONFIG_SZL_USB_CDC_ACM_ENABLE)
	target_sources(app PRIVATE szl_usb_cdc_acm.c)
	target_include_directories(app PRIVATE ./)
endif()
