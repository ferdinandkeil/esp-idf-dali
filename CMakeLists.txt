if(IDF_VERSION_MAJOR GREATER 5 OR (IDF_VERSION_MAJOR EQUAL 5 AND IDF_VERSION_MINOR GREATER_EQUAL 3))
    set(DALI_RMT_COMPONENT esp_driver_rmt)
else()
    set(DALI_RMT_COMPONENT driver)
endif()

idf_component_register(SRCS "dali.c"
                    INCLUDE_DIRS "include"
                    REQUIRES ${DALI_RMT_COMPONENT})
