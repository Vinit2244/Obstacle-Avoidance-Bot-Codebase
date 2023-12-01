#pragma once
using namespace std;
#include "esp32-hal-gpio.h"
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include <utility>
#include "freertos/portmacro.h"
#include <cinttypes>

#include "sensors.h"
#include "grid.h"
#include "gyro.h"
#include "motor.h"
#include "robo.h"
