#include "WiFi.h"
#include "ThingSpeak.h"
#include "PubSubClient.h"

const char ssid[] = "Lorem ipsum";
const char password[] = "Getlostyoutrespassers";
const char server[] = "mqtt3.thingspeak.com";

WiFiClient wifi_client;
PubSubClient mqttClient(server, 1883, wifi_client);

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}
