if(CONFIG_SZL_LEB128_ENABLE)
	target_sources(app PRIVATE szl_leb128.c)
	target_include_directories(app PRIVATE ./)
endif()