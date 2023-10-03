#include <WiFi.h>
#include <ThingSpeak.h>
#include <PubSubClient.h>
#include "esp32-hal-gpio.h"
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include <utility>
#include "freertos/portmacro.h"
#include <cinttypes>

#define TrigPinLeft 16
#define EchoPinLeft 17
#define TrigPinRight 26
#define EchoPinRight 27
#define TrigPinForward 32
#define EchoPinForward 33
#define SCL 21
#define SDA 22

#define speedOfSound 35000


#define ssid "Lorem ipsum"
#define password "Getlostyoutrespassers"

const char *server = "mqtt3.thingspeak.com";
const char *MQTTUsername = "Hi81BiQeBgcQLS8LGTgRKTc";
const char *MQTTClientID = "Hi81BiQeBgcQLS8LGTgRKTc";
const char *MQTTPass = "QLTffZasuHLK+fZiB64op7dL";

int writeChannelID = 2289111;
const char *WriteAPIKey = "4X3O813MKA5OQ8A2";

int port  = 1883;

WiFiClient wifiClient;
PubSubClient mqttClient(wifiClient);

 Adafruit_MPU6050 mpu;

void setup() {
  Serial.begin(115200);
  pinMode(TrigPinLeft, OUTPUT);
  pinMode(EchoPinLeft, INPUT);
  pinMode(TrigPinRight, OUTPUT);
  pinMode(EchoPinRight, INPUT);
  pinMode(TrigPinForward, OUTPUT);
  pinMode(EchoPinForward, INPUT);
  

  gyroSetup();


  WiFi.begin(ssid, password);
  while(WiFi.status() != WL_CONNECTED){
    Serial.println("Connecting to wifi....");
    delay(1000);
  }
  Serial.println("Wifi connected!");
  mqttClient.setServer(server, port);

}

void loop() {
  // put your main code here, to run repeatedly:

  while(mqttClient.connected() == NULL){
    Serial.println("connecting to mqtt...");
    mqttClient.connect(MQTTClientID, MQTTUsername, MQTTPass);
    delay(1000);
  }
  mqttClient.loop();

  int valueLeft = reading1();
  int valueRight = reading2();
  int valueForward = reading3();
  double gyroReadings[6];
  getGyroReading(gyroReadings);

  String data = "field1=" + String(valueLeft) + "&"; // left ultrasonic
  data += "field2=" + String(valueRight) + "&"; // right ultrasonic
  data += "field3=" + String(valueForward) + "&"; // forward ultrasonic
  data += "field4=" + String(gyroReadings[4]) + "&"; // angular vel z
  data += "field5=" + String(gyroReadings[1]) + "&"; // linear accel y


  String topicString = "channels/" + String(writeChannelID) + "/publish";
  Serial.println(topicString);
  mqttClient.publish(topicString.c_str(), data.c_str());

}

int reading1(){
  digitalWrite(TrigPinLeft, LOW);
  delayMicroseconds(2);
  digitalWrite(TrigPinLeft, HIGH);
  delayMicroseconds(10);

  digitalWrite(TrigPinLeft, LOW);

  int duration = pulseIn(EchoPinLeft, HIGH);

  int distance = duration * speedOfSound / 2 ;
  Serial.println(distance);
  return distance;
}

int reading2(){
  digitalWrite(TrigPinRight, LOW);
  delayMicroseconds(2);
  digitalWrite(TrigPinRight, HIGH);
  delayMicroseconds(10);

  digitalWrite(TrigPinRight, LOW);

  int duration = pulseIn(EchoPinRight, HIGH);

  int distance = duration * speedOfSound / 2 ;
  Serial.println(distance);
  return distance;
}

int reading3(){
  digitalWrite(TrigPinForward, LOW);
  delayMicroseconds(2);
  digitalWrite(TrigPinForward, HIGH);
  delayMicroseconds(10);

  digitalWrite(TrigPinForward, LOW);

  int duration = pulseIn(EchoPinForward, HIGH);

  int distance = duration * speedOfSound / 2 ;
  Serial.println(distance);
  return distance;
}


void gyroSetup()
{
  /*Taken directly from examples*/
  Serial.println("Adafruit MPU6050 test!");

  // Try to initialize!
  if (!mpu.begin()) 
  {
    Serial.println("Failed to find MPU6050 chip");
    while (1)
      delay(10);
  }
  Serial.println("MPU6050 Found!");

  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  Serial.print("Accelerometer range set to: ");
  Serial.println(mpu.getAccelerometerRange());

  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  Serial.print("Gyro range set to: ");
  Serial.println(mpu.getGyroRange());

  mpu.setFilterBandwidth(MPU6050_BAND_5_HZ);
  Serial.print("Filter bandwidth set to: ");
  Serial.println(mpu.getFilterBandwidth());
}

void getGyroReading(double *readings)
{
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  readings[0] = g.gyro.x;
  readings[1] = g.gyro.y;
  readings[2] = g.gyro.z;
  readings[0] = a.acceleration.x;
  readings[1] = a.acceleration.y;
  readings[2] = a.acceleration.z;
}
