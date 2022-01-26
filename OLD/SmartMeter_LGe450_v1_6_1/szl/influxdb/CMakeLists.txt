if(CONFIG_SZL_INFLUXDB_ENABLE)
	target_sources(app PRIVATE szl_influxdb.c)
	target_include_directories(app PRIVATE ./)
endif()