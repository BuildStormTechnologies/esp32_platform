#
# "main" pseudo-component makefile.
#
# (Uses default behaviour of compiling all source files in directory, adding 'include' to include path.)
#
# Don't remove this file even if its empty. 
# It results in compilation error 'undefined reference to app_main''

COMPONENT_EMBED_TXTFILES := claimCerts/aws-root-ca.pem claimCerts/certificate.pem.crt claimCerts/private.pem.key

# Print an error if the certificate/key files are missing
$(COMPONENT_PATH)/claimCerts/certificate.pem.crt $(COMPONENT_PATH)/claimCerts/private.pem.key:
	@echo "Missing PEM file $@. This file identifies the ESP32 to AWS for the example, see README for details."
	exit 1
    
