# Note: Starting with ESP-IDF v5.3, this driver requires the
# renamed component "esp_driver_rmt". Please change below.
idf_component_register(SRCS "dali.c"
                    INCLUDE_DIRS "include"
                    REQUIRES esp_driver_rmt)
