# esp32_platform

## Blogs
1. [ESP32 – IDF: AWS IoT Device Provision](https://buildstorm.com/blog/esp32-idf-aws-iot-device-provision/)
2. [ESP32 AWS-IOT OTA library on ESP-IDF](https://buildstorm.com/blog/esp32-aws-iot-ota-library-on-esp-idf/)
3. [API Reference Guide](https://buildstorm.com/docs/aws_iot_for_esp32/v1.0.0/index.html)

## Requirements

1. This library uses esp-idf v4.3.1 
2. [Download](https://dl.espressif.com/dl/esp-idf-tools-setup-online-2.9.exe?) and install the ESP-IDF tools installer for windows, or you may follow the official instructions [here](https://docs.espressif.com/projects/esp-idf/en/v4.3.1/get-started-cmake/index.html#setting-up-development-environment) for other OS.
3. Python 2.7.10 or later should have been installed by the ESP-IDF Tools installer, if not install it

---

## Example Setup
1. Follow [this article](https://buildstorm.com/blog/aws_iot_provision_by_claim/) to setup AWS and generate provisioning certificates.
2. Same certificates will be used for all examples
3. Copy the generated certificates to `..\esp32_platform\aws-iot-examples\_Certificates\claimCerts` folder and rename them as follows
   1. `aws-root-ca.pem` 
   2. `claim-certificate.pem` 
   3. `claim-private.pem.key` 
4. Update the following WiFi and AWS parameters in `app_config.h` of the example

```
#define TEST_WIFI_SSID     "YOUR WIFI SSID"
#define TEST_WIFI_PASSWORD "YOUR WIFI PWD"

#define AWS_IOT_MQTT_HOST "YOUR AWS HOST"
#define AWS_IOT_MQTT_PORT  8883
#define AWS_PROVISION_TEMPLATE_NAME "YOUR PROVISION TEMPLATE"
```

---

## Building the project

1. Open the `ESP-IDF 4.3.1 CMD` command prompt
2. Navigate to `..\<example>` folder
3. Build Command
    ```sh
    idf.py build
    ```
4. Erase the chip (first time only)
    ```sh
    idf.py -p <SERIAL_PORT> erase_flash
    ```
5. Flash Command
    ```sh
    idf.py -p <SERIAL_PORT> flash monitor
    ```

---

## Testing
1. On first boot, device will register itself and reboot ![](testingResultImage\firstBoot.png)
2. Open the [AWS IoT console](https://console.aws.amazon.com/iot/home), and in the left menu, choose Test to open the MQTT client.
3. Following image shows subscribe/publish functionality
![](testingResultImage/mqttPubSub.png)
5. Testing shadow update
   1. It requires creating a default shadow and publishing message to it. Please watch the video for detailed process
6. Testing OTA
   1. It requires files to S3 bucket and creating jobs. Please watch the video for detailed process

---

## Device Menu
1. On serial terminal, press `m` to display device menu 

![](testingResultImage/deviceMenu.png)

