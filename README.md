# ESW-Project-It-Just-Works
This repository is for the team members of the ESW project team (It Just Works) for collaborating on the Sem3 ESW project of making an obstacle avoidance robot using artificial potential field method

# Usage Instructions:
0. On your Arduino IDE, click on "Tools" in the menu bar, and change the "Partition Scheme" to "No OTA (2MB APP/2MB SPIFFS)".
1. Upload the code from esw/esw.ino onto the ESP32 module on the robot.
2. Take out the USB from your PC, and connect it a 5V power outlet, like a power bank.
3. Switch on your mobile hotspot (do remember to replace your ssid and password in the code)
4. Switch on Bluetooth on your phone and pair with the ES32 (its name will appear as "ItJustWorksBot").
5. Launch the "Serial Bluetooth Monitor" app on your phone.
6. Under "Devices", connect with the ESP32.
7. Send a '1' (without quotes) via the app to start the robot.
8. Watch as it moves around, avoiding obstacles.
9. You can see real-time data being uploaded onto our website.
10. To switch it off, send a '0' (without quotes).

# Required Libraries
1. Adafruit MPU6050 (and all its depedencies) for the gyroscope
2. Adafruit Unified Sensor
3. Adafruit BusIO


Link to website github: https://github.com/someyuck/ESW-Project-It-Just-Works-Webhost


























