****************************************** /
//  https://myhomethings.eu               //
//  Smart Alternative Switch - ESP8266    //
//  Board: NodeMCU 1.0 ESP-12E            //
/******************************************/

#include <ESP8266WiFi.h>
#include <PubSubClient.h>

  const char* ssid = "SSID";
const char* password = "Password";
const char* mqtt_server = "192.168.x.xxx";

WiFiClient espClient;
PubSubClient client(espClient);

int relayPin = D5;
int lightControllPin = D2;
long previousMillis = 0;
int relayState = 1;
int switchState = 0;
int switchFlag = 0;


void setup_wifi() {
  delay(100);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
  randomSeed(micros());
}

void reconnect() {
  while (!client.connected()) {
    String clientId = "ESP8266-Alternative-Switch";

    if (client.connect(clientId.c_str())) {
      client.subscribe("Lamp_topic");
    } else {
      delay(6000);
    }
  }
}

void callback(char* topic, byte* payload, unsigned int length) {
  payload[length] = '128';
/******************************************/
//  https://myhomethings.eu               //
//  Smart Alternative Switch - ESP8266    //
//  Board: NodeMCU 1.0 ESP-12E            //
/******************************************/
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
    const char* ssid = "SSID";
  const char* password = "Password";
  const char* mqtt_server = "192.168.x.xxx";
  WiFiClient espClient;
  PubSubClient client(espClient);
  int relayPin = D5;
  int lightControllPin = D2;
  long previousMillis = 0;
  int relayState = 1;
  int switchState = 0;
  int switchFlag = 0;
  void setup_wifi() {
    delay(100);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
    }
    randomSeed(micros());
  }
  void reconnect() {
    while (!client.connected()) {
      String clientId = "ESP8266-Alternative-Switch";
      if (client.connect(clientId.c_str())) {
        client.subscribe("Lamp_topic");
      } else {
        delay(6000);
      }
    }
  }
  void callback(char* topic, byte* payload, unsigned int length) {
    payload[length] = '\0';
    String strTopic = String(topic);
    String strPayload = String((char*)payload);
    if (strTopic == "Lamp_topic" && switchFlag == 0) {
      if (strPayload == "false") {
        if (digitalRead(lightControllPin) == LOW) {
          if (relayState == 1) {
            digitalWrite(relayPin, LOW);
            relayState = 0;
          } else {
            digitalWrite(relayPin, HIGH);
            relayState = 1;
          }
        }
      }
      if (strPayload == "true") {
        if (digitalRead(lightControllPin) == HIGH) {
          if (relayState == 1) {
            digitalWrite(relayPin, LOW);
            relayState = 0;
          } else {
            digitalWrite(relayPin, HIGH);
            relayState = 1;
          }
        }
      }
    }
  }
  void setup() {
    setup_wifi();
    client.setServer(mqtt_server, 1883);
    client.setCallback(callback);
    pinMode(relayPin, OUTPUT);
    pinMode(lightControllPin, INPUT);
    digitalWrite(relayPin, HIGH);
  }
  void loop() {
    unsigned long Millis = millis();
    if (Millis - previousMillis >= 1000) {
      previousMillis = Millis;
      switchFlag = 0;
    }
    if (!client.connected()) {
      reconnect();
    }
    client.loop();
    if (digitalRead(lightControllPin) == LOW) {
      if (switchState == 0) {
        client.publish("Lamp_topic", "true");
        switchState = 1;
        switchFlag = 1;
      }
    }
    if (digitalRead(lightControllPin) == HIGH) {
      if (switchState == 1) {
        client.publish("Lamp_topic", "false");
        switchState = 0;
        switchFlag = 1;
      }
    }
  }
  String strTopic = String(topic);
  String strPayload = String((char*)payload);

  if (strTopic == "Lamp_topic" && switchFlag == 0) {
    if (strPayload == "false") {
      if (digitalRead(lightControllPin) == LOW) {
        if (relayState == 1) {
          digitalWrite(relayPin, LOW);
          relayState = 0;
        } else {
          digitalWrite(relayPin, HIGH);
          relayState = 1;
        }
      }
    }

    if (strPayload == "true") {
      if (digitalRead(lightControllPin) == HIGH) {
        if (relayState == 1) {
          digitalWrite(relayPin, LOW);
          relayState = 0;
        } else {
          digitalWrite(relayPin, HIGH);
          relayState = 1;
        }
      }
    }
  }
}

void setup() {
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);

  pinMode(relayPin, OUTPUT);
  pinMode(lightControllPin, INPUT);
  digitalWrite(relayPin, HIGH);
}

void loop() {
  unsigned long Millis = millis();
  if (Millis - previousMillis >= 1000) {
    previousMillis = Millis;
    switchFlag = 0;
  }

  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  if (digitalRead(lightControllPin) == LOW) {
    if (switchState == 0) {
      client.publish("Lamp_topic", "true");
      switchState = 1;
      switchFlag = 1;
    }
  }

  if (digitalRead(lightControllPin) == HIGH) {
    if (switchState == 1) {
      client.publish("Lamp_topic", "false");
      switchState = 0;
      switchFlag = 1;
    }
  }
}