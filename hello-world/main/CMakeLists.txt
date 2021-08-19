idf_component_register(SRCS
                           "app_main.c"
                       INCLUDE_DIRS 
                           "."
                           "../../esp32_Lib"
)

# Import the library, specifying a target name and the library path.
# The private dependencies of the library is also specified.
add_prebuilt_library(esp32_platform_comp
                        "../../esp32_Lib/libesp32_platform_comp.a"
                     PRIV_REQUIRES 
                        esp_http_client
                        app_update
                        bt
                        mqtt
                        spi_flash
                        log
)

# `main` calls a function from the library, so link it to `main`
target_link_libraries(${COMPONENT_LIB} PRIVATE esp32_platform_comp)

