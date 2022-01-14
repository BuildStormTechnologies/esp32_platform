#
# "main" pseudo-component makefile.
#
# (Uses default behaviour of compiling all source files in directory, adding 'include' to include path.)
#
# Don't remove this file even if its empty. 
# It results in compilation error 'undefined reference to app_main''

COMPONENT_EMBED_TXTFILES := ../../_Certificates/claimCerts/aws-root-ca.pem ../../_Certificates/claimCerts/claim-certificate.pem.crt ../../_Certificates/claimCerts/claim-private.pem.key

# Print an error if the certificate/key files are missing
$(COMPONENT_PATH)../../_Certificates/claimCerts/claim-certificate.pem.crt $(COMPONENT_PATH)../../_Certificates/claimCerts/claim-private.pem.key:
	@echo "Missing PEM file $@. This file identifies the ESP32 to AWS for the example, see README for details."
	exit 1
    
