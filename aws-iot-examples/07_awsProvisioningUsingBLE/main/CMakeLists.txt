
# Register all the required components
idf_component_register(
                        SRC_DIRS "."
                        INCLUDE_DIRS "."
                        PRIV_REQUIRES bs_esp32_platform
)


# Embade the AWS certificate in the binary
target_add_binary_data(${COMPONENT_TARGET} "../../_Certificates/thingCerts/aws-root-ca.pem" TEXT)
target_add_binary_data(${COMPONENT_TARGET} "../../_Certificates/thingCerts/thing-certificate.pem.crt" TEXT)
target_add_binary_data(${COMPONENT_TARGET} "../../_Certificates/thingCerts/thing-private.pem.key" TEXT)

target_add_binary_data(${COMPONENT_TARGET} "../../_Certificates/claimCerts/aws-root-ca.pem" TEXT)
target_add_binary_data(${COMPONENT_TARGET} "../../_Certificates/claimCerts/claim-certificate.pem.crt" TEXT)
target_add_binary_data(${COMPONENT_TARGET} "../../_Certificates/claimCerts/claim-private.pem.key" TEXT)

