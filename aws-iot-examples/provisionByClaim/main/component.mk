#
# "main" pseudo-component makefile.
#
# (Uses default behaviour of compiling all source files in directory, adding 'include' to include path.)
#
# Don't remove this file even if its empty. 
# It results in compilation error 'undefined reference to app_main''

COMPONENT_EMBED_TXTFILES := certs/aws-root-ca.pem certs/certificate.pem.crt certs/private.pem.key claimCert/cert-certificate.pem.crt claimCert/cert-private.pem.key

# Print an error if the certificate/key files are missing
$(COMPONENT_PATH)/certs/certificate.pem.crt $(COMPONENT_PATH)/certs/private.pem.key:
	@echo "Missing PEM file $@. This file identifies the ESP32 to AWS for the example, see README for details."
	exit 1
    
