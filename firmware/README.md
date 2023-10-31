# Kaia.ai Arduino firmware

[Kaia.ai](https://kaiaai) is a platform for 3D-printable pet robots. Please sign up for an early launch invite [here](https://remake.ai).

This repo contains Arduino ESP32 firmware for [Kaia.ai](https://kaia.ai) home pet robots.
This firmware uses a Micro-ROS [library](https://github.com/kaiaai/micro_ros_arduino_kaia) for Arduino.

## Bringup

- Launch Kaia.ai software stack on your PC, see instructions for
[developers](https://github.com/kaiaai/docker/tree/main/kaiaai-ros-dev) (with ROS2 dev tools and GUI) and
[end users](https://github.com/kaiaai/docker/tree/main/kaiaai-ros) (no dev tools, GUI).

- Power up your ESP32 Dev Module.
- When powered up for the first time after firmware upload:
  - Your ESP32 Dev Module should set up a 2.4GHz WiFi network named `KAIAAI-WIFI`.
  - Connect to `KAIAAI-WIFI` using your PC, smartphone or tablet. If your device has connections other than WiFi,
    disable those other connections. For example, put your smartphone in "Airplane Mode", then enable WiFi and
    connect to `KAIAAI-WIFI`. If prompted "This network has no internet access. Would you like to stay connected?",
    press "Yes".
  - Your ESP32 module's LED should light up in solid color, no blinking, while `KAIAAI-WIFI` network is active.

![esp32_wifi_manager_v2](https://github.com/makerspet/makerspet_snoopy/assets/143911662/6df0288d-7b60-4bf3-a4f6-45accb5bbd55)

- Open a browser and navigate to [http://192.168.4.1](http://192.168.4.1). You should see a WiFi configuration
    page.
  - Enter your home WiFi credentials and press `Connect`.
  - Your ESP32 module will store your WiFi credentials in its permanent memory and will attempt
    connecting to your home WiFi.
  - If your ESP32 module fails to connect to your home WiFi (e.g. wrong password), your WiFi module will
    recreate its `KAIAAI-WIFI` network, so you can retry the WiFi configuration steps above.
  - Keep in mind that ESP32 works only with 2.4GHz networks. You will not be able to see or connect
    to any 5GHz networks.

![esp32_wifi_manager_response_v2](https://github.com/makerspet/makerspet_snoopy/assets/143911662/e670369a-0b22-463c-a6bd-4e617c4edc2d)

- Once connected to your home WiFi, your ESP32 module will attempt to connect to your local PC running the
Kaia.ai ROS2 software stack (in Docker).
  - Upon successful connection your local PC should print out some diagnostic information.
- If your ESP32 module fails to connect to your PC, your ESP32 module will report the error by blinking a number of times:
  - One long blink followed by a number of short blinks. Count the number of short blinks to determine the error code.
  - Once you have the error code, open `kaia-esp32.h` and look up the `ERR_*` label that matches the error code.
    That will tell you the reason for the failure.
  - Alternatively, connect your ESP32 module to your Arduino IDE using a USB cable, select the Arduino IDE COM port
    by clicking Tools -> Port, click Tools -> Serial Monitor to open the Arduino IDE console and 
    set its baud rate to 115200. Reset your ESP32 module by pressing its EN button and observe ESP32 printing
    diagnostic information while establishing its WiFi network, a WiFi connection, a PC connection and associated
    error messages, if any.

## Troubleshooting
- If ESP32 fails to connect to our WiFi or your local PC:
  - Launch Arduino IDE on your PC.
  - Connect ESP32 to your PC using a USB cable.
  - Launch Tools -> Serial Monitor in your Arduino IDE.
  - Reset your ESP32 by pressing it `En` button.
  - Inspect the debug output in the Serial Monitor console as ESP32 attempts to establish its WiFi
    connection.
  - Once the WiFi connection succeed, keep inspecting the Serial Monitor's debug output
    as ESP32 attempts connecting to your local PC.
- Try resetting your ESP32 by pushing the `En` button. Sometimes this fixes WiFi connection problems.
- Try "factory-resetting" your ESP32, see instructions below.
- Try turning your router or hotspot off and on. My personal Google Pixel 7's hotspot has a bug
  that prevents ESP32 (as well as my laptop) re-connecting successfully. Only the first
  connection attempt succeeds. Connecting a second time succeeds only once I manually turn
  the hotspot off and then back on.

## Installation
- Download the Kaia.ai firmware project code from this [repo](https://github.com/kaiaai/arduino_fw)
- Install the Micro-ROS Kaia.ai library using Arduino Library Manager. Learn more [here](https://github.com/kaiaai/micro_ros_arduino_kaia)
- open the downloaded `snoopy_esp32.ino` project file in your Arduino IDE
- In your Arduino IDE, configure Tools -> Board as "ESP32 Dev Module" and leave the board settings at their defaults
- Install th ESP32 Sketch Data Upload tool, instructions [here](https://randomnerdtutorials.com/install-esp32-filesystem-uploader-arduino-ide/)
- Cick the Arduino IDE build button.
  - The project should build successfully.
- Configure the Arduino IDE COM port for firmware upload by clicking Tools -> Port and selecting the port associated
  with your ESP32. Usually there is only one port available - just try selecting it.
- Click the Arduino IDE build-and-upload button.
  - Once the project builds successfully, you should `.....` indicating the firmware upload is ready to start.
  - Press the `EN` button on your ESP32 Dev Module for 2-3 seconds.
  - The upload should start.
- Upload sketch data.
  - Press and hold the `EN` button on your ESP32 Dev Module.
  - Click Tools -> ESP32 Sketch Data Upload
  - The sketch data upload should print out some `SPIFFS` diagnostic information.
  - Release the `EN` button on your ESP32 Dev Module.
  - The sketch data upload should finish successfully.

## Factory reset
You can wipe out stored settings, including WiFi SSID and password, as follows:
- press and release ESP32 `EN` (reset) button
- press and hold ESP32 `Boot` button for at least 6 seconds
- release ESP32 Boot button
- ESP32 should blink, 5 times slowly - 1 blink per 2 seconds
- ESP32 will reboot after that and reenter its WiFi configuration mode
- Every time you upload firmware to your ESP32, the stored WiFi settings get wiped.
- Make sure you are connecting ESP32 to a 2.4GHz network. ESP32 does not support 5GHz networks.

## Modding the robot and its firmware
- Start with an existing Kaia.ai robot, e.g. [Snoopy](https://github.com/makerspet/makerspet_snoopy/)
- If needed, mod the robot's 3D-printable robot body. You can use [Snoopy's design](https://github.com/makerspet/makerspet_snoopy/tree/main/hardware) as a starting point
- If needed, mod the robot's description (i.e. sofware configuration and model), see [Snoopy's URDF](https://github.com/makerspet/makerspet_snoopy/tree/main/urdf)
- If needed, mod the robot's firmware - use this repo as a starting point
