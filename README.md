# ESW-Project-It-Just-Works

Welcome to the ESW Project Team's repository for the "It Just Works" obstacle avoidance robot. This repository is dedicated to collaboration among team members working on the Sem3 ESW project, focusing on implementing an obstacle avoidance robot using the artificial potential field method.

## Contributors:

- Vinit Mehta
- Samyak Mishra
- Abhinav Raundhal
- Yash Shinde

**Note: Developed during the 3rd semester for the course "Embedded System Workshop."**

## Usage Instructions:

Follow these steps to deploy and operate the obstacle avoidance robot:

0. In your Arduino IDE, navigate to "Tools" in the menu bar, and set the "Partition Scheme" to "No OTA (2MB APP/2MB SPIFFS)."
1. Upload the code from `esw/esw.ino` onto the ESP32 module installed on the robot.
2. Disconnect the USB cable from your PC, and power the robot using a 5V power source, such as a power bank.
3. Activate your mobile hotspot (ensure to update your SSID and password in the code).
4. Turn on Bluetooth on your phone and pair it with the ESP32; the device name will be displayed as "ItJustWorksBot."
5. Launch the "Serial Bluetooth Monitor" app on your phone.
6. In the app, under "Devices," connect to the ESP32.
7. Send a '1' (without quotes) via the app to initiate the robot's movement.
8. Observe as the robot navigates, avoiding obstacles in its path.
9. Real-time data is continuously uploaded to our website.
10. To power off the robot, send a '0' (without quotes).

## Required Libraries:

Make sure to install the following Arduino libraries before uploading the code:

1. **Adafruit MPU6050:** Required for gyroscope functionality.
2. **Adafruit Unified Sensor:** Essential for sensor integration.
3. **Adafruit BusIO:** Necessary for I2C communication.

## Website Repository:

For the web hosting part of the project, check out our website's GitHub repository [here](https://github.com/someyuck/ESW-Project-It-Just-Works-Webhost).

Feel free to contribute, report issues, or provide feedback. Happy coding!
