idf_component_register(
                        INCLUDE_DIRS
                            "."
                            "lib/include"
                            "aws_lib/include"
)

# Import the library, specifying a target name and the library path.
# The private dependencies of the library is also specified.
add_prebuilt_library(
                     bs_esp32_platform
                        "bs_esp32_platform.a"
                     PRIV_REQUIRES 
                        esp_http_client
                        esp-tls
                        app_update
                        mqtt
                        spi_flash
                        nvs_flash
                        bt
                        log
)

# `main` calls a function from the library, so link it to `main`
target_link_libraries(${COMPONENT_LIB} INTERFACE bs_esp32_platform)

