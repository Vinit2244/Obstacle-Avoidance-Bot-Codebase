#define left_trigger                16
#define left_echo                   17

#define right_trigger               26
#define right_echo                  27

#define center_trigger              32
#define center_echo                 33

#define right_diagonal_trigger      18
#define right_diagonal_echo         19

#define left_diagonal_trigger       2
#define left_diagonal_echo          15

#define speed_of_sound 35000

#define STOP    0
#define FORWARD 1
#define RIGHT   2
#define LEFT    3

#include <WiFi.h>
#include <ThingSpeak.h>
#include <PubSubClient.h>
#include "BluetoothSerial.h"

BluetoothSerial SerialBT;

char t;
int BT_on_off_status = 0;
char mode = 'a';  // In auto mode by default

#define Shinde_ssid     "Hello.c"
#define Shinde_password "pwla1953"
#define Samyak_ssid     "Lorem ipsum"
#define Samyak_password "Getlostyoutrespassers"

#define ssid         Shinde_ssid
#define password     Shinde_password
#define server       "mqtt3.thingspeak.com"
#define MQTTUsername "Hi81BiQeBgcQLS8LGTgRKTc"
#define MQTTClientID "Hi81BiQeBgcQLS8LGTgRKTc"
#define MQTTPass     "QLTffZasuHLK+fZiB64op7dL"
#define channelID    2289111
#define WriteAPIKey  "4X3O813MKA5OQ8A2"
#define port         1883
#define HIGH_T       150 // in miliseconds
#define LOW_T        20 // in miliseconds
#define maxSpeed     1000
#define danger       30.0 // cms

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


/* gloabls */
int status = STOP;
const int leftMotor[2] = { 4, 5 };
const int rightMotor[2] = { 13, 12 };

WiFiClient wifiClient;
PubSubClient mqttClient(wifiClient);

void set_speed(int leftSpeed, int rightSpeed)
{
  int leftCheck = leftSpeed < 0;
  analogWrite(leftMotor[leftCheck], abs(leftSpeed));
  analogWrite(leftMotor[leftCheck ^ 1], 0);

  int rightCheck = rightSpeed < 0;
  analogWrite(rightMotor[rightCheck], abs(rightSpeed));
  analogWrite(rightMotor[rightCheck ^ 1], 0);
}

float take_reading(int trig_pin, int echo_pin)
{
  digitalWrite(trig_pin, LOW);
  delayMicroseconds(2);
  digitalWrite(trig_pin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig_pin, LOW);

  int time = pulseIn(echo_pin, HIGH);
  float distance = ((float)time / 1000000) * speed_of_sound;  // in cms
  return (distance / 2);
}

void stop()
{
  set_speed(0, 0);
}

void go_left(int turn_time)
{
  if (status == LEFT)
  {
    // do nothing
  }
  else
  {
    set_speed(-maxSpeed, maxSpeed);
  }
  delay(turn_time);
}

void go_right(int turn_time)
{
  if (status == RIGHT)
  {
    // do nothing
  }
  else
  {
    set_speed(maxSpeed, -maxSpeed);
  }
  delay(turn_time);
}

void go_straight()
{
  if (status == FORWARD)
  {
    // do nothing
  }
  else
  {
    set_speed(maxSpeed, maxSpeed);
  }
}

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
  data += "field4=" + String(BT_on_off_status) + "&"; // on/off status

  String topicString = "channels/" + String(channelID) + "/publish";
  Serial.println(topicString);
  mqttClient.publish(topicString.c_str(), data.c_str());
}

void setup()
{
  for (int i = 0; i < 2; i++)
  {
    pinMode(leftMotor[i], OUTPUT);
    pinMode(rightMotor[i], OUTPUT);
  }

  pinMode(left_trigger, OUTPUT);
  pinMode(right_trigger, OUTPUT);
  pinMode(center_trigger, OUTPUT);
  pinMode(left_diagonal_trigger, OUTPUT);
  pinMode(right_diagonal_trigger, OUTPUT);
  pinMode(left_echo, INPUT);
  pinMode(right_echo, INPUT);
  pinMode(center_echo, INPUT);
  pinMode(left_diagonal_echo, INPUT);
  pinMode(right_diagonal_echo, INPUT);

  Serial.begin(115200);
  SerialBT.begin("ItJustWorksBot");
  Serial.println("Bluetooth started...");
  
  wifi_mqtt_setup();  
  ThingSpeak.begin(wifiClient);
}

void decide_what_to_do(int result)
{
    if(result == 0b00000)
    {
        stop();
        status = STOP;
    }
    else if(result == 0b00001)
    {
        go_right(HIGH_T);
        status = RIGHT;
    }
    else if(result == 0b00010)
    {
        go_right(LOW_T);
        status = RIGHT;
    }
    else if(result == 0b00011)
    {
        go_right(HIGH_T/2);
        status = RIGHT;
    }
    else if(result == 0b00100)
    {
        go_straight();
        status = FORWARD;
    }
    else if(result == 0b00101)
    {
        go_right(HIGH_T/2);
        status = RIGHT;
    }
    else if(result == 0b00110)
    {
        go_right(LOW_T*2);
        status = RIGHT;
    }
    else if(result == 0b00111)
    {
        go_right(LOW_T*2);
        status = RIGHT;
    }
    else if(result == 0b01000)
    {
        go_left(LOW_T);
        status = LEFT;
    }
    else if(result == 0b01001)
    {
        go_right(HIGH_T/2);     //prioritise right
        status = RIGHT;
    }
    else if(result == 0b01010)
    {
        go_right(HIGH_T/2);     //prioritise right
        status = RIGHT;
    }
    else if(result == 0b01011)
    {
        go_right(HIGH_T/2);
        status = RIGHT;
    }
    else if(result == 0b01100)
    {
        go_left(LOW_T/2);
        status = LEFT;
    }
    else if(result == 0b01101)
    {
        go_left(LOW_T/2);
        status = LEFT;
    }
    else if(result == 0b01110)
    {
        go_straight();
        status = FORWARD;
    }
    else if(result == 0b01111)
    {
        go_right(LOW_T/2);
        status = RIGHT;
    }
    else if(result == 0b10000)
    {
        go_left(HIGH_T);
        status = LEFT;
    }
    else if(result == 0b10001)
    {
        go_right(HIGH_T/2);     //prioritise right
        status = RIGHT;
    }
    else if(result == 0b10010)
    {
        go_right(HIGH_T/2);     //prioritise right
        status = RIGHT;
    }
    else if(result == 0b10011)
    {
        go_right(HIGH_T/2);
        status = RIGHT;
    }
    else if(result == 0b10100)
    {
        go_left(HIGH_T/2);
        status = LEFT;
    }
    else if(result == 0b10101)
    {
        go_right(HIGH_T/2);     //prioritise right
        status = RIGHT;
    }
    else if(result == 0b10110)
    {
        go_right(LOW_T/2);
        status = RIGHT;
    }
    else if(result == 0b10111)
    {
        go_right(LOW_T/2);
        status = RIGHT;
    }
    else if(result == 0b11000)
    {
        go_left(HIGH_T/2);
        status = LEFT;
    }
    else if(result == 0b11001)
    {
        go_left(HIGH_T/2);
        status = LEFT;
    }
    else if(result == 0b11010)
    {
        go_left(HIGH_T/2);
        status = LEFT;
    }
    else if(result == 0b11011)
    {
        go_right(HIGH_T/2);     //prioritise right
        status = RIGHT;
    }
    else if(result == 0b11100)
    {
        go_left(LOW_T*2);
        status = LEFT;
    }
    else if(result == 0b11101)
    {
        go_left(LOW_T/2);
        status = LEFT;
    }
    else if(result == 0b11110)
    {
        go_left(LOW_T/2);
        status = LEFT;
    }
    else if(result == 0b11111)
    {
        go_straight();
        status = FORWARD;
    }

}

void main_loop()
{
  mqtt_loop();
  float left_distance = take_reading(left_trigger, left_echo);
  float center_distance = take_reading(center_trigger, center_echo);
  float right_distance = take_reading(right_trigger, right_echo);
  float left_diagonal_distance = take_reading(left_diagonal_trigger, left_diagonal_echo);
  float right_diagonal_distance = take_reading(right_diagonal_trigger, right_diagonal_echo);

  Serial.print("left distance: ");
  Serial.println(left_distance);
  Serial.print("left diagonal distance: ");
  Serial.println(left_diagonal_distance);
  Serial.print("center distance: ");
  Serial.println(center_distance);
  Serial.print("right diagonal distance: ");
  Serial.println(right_diagonal_distance);
  Serial.print("right distance: ");
  Serial.println(right_distance);

  // publish to thingspeak
  publish(left_distance, right_distance, center_distance);
  
  // actuation
  int l = 1;
  int c = 1;
  int r = 1;
  int d_l = 1;
  int d_r = 1;

  if (left_distance < danger)
  {
    l = 0;
  }

  if (left_diagonal_distance < danger)
  {
    d_l = 0;
  }

  if (center_distance < danger)
  {
    c = 0;
  }

  if (right_diagonal_distance < danger)
  {
    d_r = 0;
  }
  
  if (right_distance < danger)
  {
    r = 0;
  }

  int result = 16 * l + 8 * d_l + 4 * c + 2 * d_r + r;
  decide_what_to_do(result);

}

int on_off_flag = 0;

void keep_going_forward()
{
  
}

void loop()
{
  if (SerialBT.available())
  {
    t = SerialBT.read();
    Serial.println(t);
    if (t == '1')
    {
      BT_on_off_status = 1;
    }
    else if (t == '0')
    {
      BT_on_off_status = 0;
    }
    else if (t == 'm')
    {
      if (BT_on_off_status == 1)
      {
        // Do nothing and carry on as usual in auto mode
      }
      else
      {
        // Change the mode to manual
        mode = 'm';
      }
    }
  }
  if (mode == 'a')
  {
    // Automatic mode
    if (BT_on_off_status == 1)
    {
      main_loop();
      on_off_flag = 0;
    }
    else
    {
      stop();
      status = STOP;

      if(on_off_flag == 0)
      {
        publish(take_reading(left_trigger, left_echo), take_reading(right_trigger, right_echo), take_reading(center_trigger, center_echo));
        on_off_flag = 1;
      }
    }
  }
  else
  {
    // Manual mode
    while (1)
    {
      if (SerialBT.available())
      {
        t = SerialBT.read();
        Serial.println(t);
        if (t == 'a')
        {
          stop();
          status = STOP;
          mode = 'a';
          break;
        }
        else if (t == 'l')
        {
          // turn left
          set_speed(-maxSpeed, maxSpeed);
          delay(1279);
          stop();
          status = STOP;
        }
        else if (t == 'r')
        {
          // turn right
          set_speed(maxSpeed, -maxSpeed);
          delay(1000);
          stop();
          status = STOP;
        }
        else if (t == 'f')
        {
          // go straight and stop is going to bump
          while (1)
          {
            set_speed(maxSpeed, maxSpeed);
            // If no input given keep going straight but also keep checking if we can go straight or not if not then just stop
            float cd = take_reading(center_trigger, center_echo);
            Serial.println(cd);
            if (cd < danger)
            {
              Serial.println("I am here.");
              stop();
              status = STOP;
              return;
            }
            else
            {
              delay(100);
            }

            if (SerialBT.available())
            {
              t = SerialBT.read();
              Serial.println(t);

              if (t == '0')
              {
                stop();
                status = STOP;
                return;
              }
              else if (t == 'a')
              {
                stop();
                status = STOP;
                mode = 'a';
                return;
              }
            }
          }
        }
        else if (t == '0')
        {
          stop();
        }
      }
    }
  }
}
