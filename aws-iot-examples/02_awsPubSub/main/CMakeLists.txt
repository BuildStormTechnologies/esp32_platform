idf_component_register(SRCS
                        SRC_DIRS "."
                        INCLUDE_DIRS "."
			PRIV_REQUIRES bs_esp32_platform 

)



target_add_binary_data(${COMPONENT_TARGET} "../../_Certificates/thingCerts/aws-root-ca.pem" TEXT)
target_add_binary_data(${COMPONENT_TARGET} "../../_Certificates/thingCerts/thing-certificate.pem.crt" TEXT)
target_add_binary_data(${COMPONENT_TARGET} "../../_Certificates/thingCerts/thing-private.pem.key" TEXT)
