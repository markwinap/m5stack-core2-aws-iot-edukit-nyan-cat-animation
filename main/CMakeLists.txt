set(SOURCES app_main.c)
idf_component_register(SRC_DIRS "."
                    REQUIRES "core2forAWS" "esp-cryptoauthlib" "fft" "nvs_flash")
