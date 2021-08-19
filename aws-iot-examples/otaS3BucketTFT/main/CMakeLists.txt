idf_component_register(SRCS
                           "app_main.c"
                           "lib_display_TJCTM24024.c"
                           "../components/tft/tft.c"
                   "../components/tft/DefaultFont.c"
                   "../components/tft/tftspi.c"
                   "../components/tft/def_small.c"
                   "../components/tft/SmallFont.c"
                   "../components/tft/tooney32.c"
                   "../components/tft/minya24.c"
                   "../components/tft/comic24.c"
                   "../components/tft/Ubuntu16.c"
                   "../components/tft/DejaVuSans24.c"
                   "../components/tft/DejaVuSans18.c"
                   "../components/spidriver/spi_master_lobo.c"
                       INCLUDE_DIRS 
                           "."
                           "../../../esp32_Lib"
                           "../components/tft"
                            "../components/spidriver"
)

# Import the library, specifying a target name and the library path.
# The private dependencies of the library is also specified.
add_prebuilt_library(esp32_platform_comp
                        "../../../esp32_Lib/libesp32_platform_comp.a"
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


target_add_binary_data(${COMPONENT_TARGET} "claimCerts/aws-root-ca.pem" TEXT)
target_add_binary_data(${COMPONENT_TARGET} "claimCerts/certificate.pem.crt" TEXT)
target_add_binary_data(${COMPONENT_TARGET} "claimCerts/private.pem.key" TEXT)
