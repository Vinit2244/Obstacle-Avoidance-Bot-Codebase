#define left_trigger  16
#define left_echo     17

#define right_trigger 26
#define right_echo    27

#define center_trigger 32
#define center_echo    33

#define speed_of_sound 35000

#define STOP    0
#define FORWARD 1
#define RIGHT   2
#define LEFT    3


#include <WiFi.h>
#include <ThingSpeak.h>
#include <PubSubClient.h>
// #include "esp32-hal-gpio.h"
// #include <Adafruit_MPU6050.h>
// #include <Adafruit_Sensor.h>
// #include <Wire.h>
// #include <utility>
// #include "freertos/portmacro.h"
// #include <cinttypes>

#define ssid "Lorem ipsum"
#define password "Getlostyoutrespassers"

const char *server = "mqtt3.thingspeak.com";
const char *MQTTUsername = "Hi81BiQeBgcQLS8LGTgRKTc";
const char *MQTTClientID = "Hi81BiQeBgcQLS8LGTgRKTc";
const char *MQTTPass = "QLTffZasuHLK+fZiB64op7dL";

int writeChannelID = 2289111;
const char *WriteAPIKey = "4X3O813MKA5OQ8A2";

int port  = 1883;

/* robo functions */
void set_speed(int leftSpeed, int rightSpeed);
float take_reading(int trig_pin, int echo_pin);
void stop();
void go_left(int turn_time);
void go_right(int turn_time);
void go_straight();

/* IOT functions */
void wifi_mqtt_setup();
void mqtt_loop();
void publish(float valueLeft, float valueRight, float valueForward);