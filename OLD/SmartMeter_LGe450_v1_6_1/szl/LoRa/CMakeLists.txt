if(CONFIG_SZL_LORA_ENABLE)
	target_sources(app PRIVATE szl_lora.c)
	target_include_directories(app PRIVATE ./)
endif()