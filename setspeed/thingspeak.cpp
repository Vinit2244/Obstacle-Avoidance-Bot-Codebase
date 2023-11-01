#include "defs.h"

WiFiClient wifiClient;
PubSubClient mqttClient(wifiClient);

void wifi_mqtt_setup()
{
  WiFi.begin(ssid, password);
  while(WiFi.status() != WL_CONNECTED){
    Serial.println("Connecting to wifi....");
    delay(1000);
  }
  Serial.println("Wifi connected!");
  mqttClient.setServer(server, port);
}

void mqtt_loop()
{
  while(mqttClient.connected() == NULL){
    Serial.println("connecting to mqtt...");
    mqttClient.connect(MQTTClientID, MQTTUsername, MQTTPass);
    delay(1000);
  }
  mqttClient.loop();
}

void publish(float valueLeft, float valueRight, float valueForward)
{
  String data = "field1=" + String(valueLeft) + "&"; // left ultrasonic
  data += "field2=" + String(valueRight) + "&"; // right ultrasonic
  data += "field3=" + String(valueForward) + "&"; // forward ultrasonic

  String topicString = "channels/" + String(writeChannelID) + "/publish";
  Serial.println(topicString);
  mqttClient.publish(topicString.c_str(), data.c_str());
}