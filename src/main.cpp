/**
 * Main device "Forwarder Node"
 */
#define APP_VERSION "0.1"

// Configuration
#define device_id       "gateway01"
#define sensor_id       "s01"
#define ssid            "wifinya"
#define pass            "passnya"
#define broker          "localhost"
#define broker_port     5883
#define LoRa_Freq       923E6

// LoRa pinouts
#define SCK_PIN     5
#define MISO_PIN    19
#define MOSI_PIN    27
#define SS_PIN      18
#define RST_PIN     23
#define DIO0_PIN    26

#include <Arduino.h>
#include "gateway.h"

String mqtt_topic = String(device_id) + "/" + String(sensor_id) + "/";
void mqttCallback(String topic, byte* _payload, unsigned int _length);

void setup() {
    Serial.begin(9600);
    Serial.println();

    gateway.host.connectWiFi(ssid, pass);
    Serial.println(gateway.host.getHostAddress());
    gateway.host.initHost();
    gateway.host.setMQTTBroker(broker, broker_port);
    gateway.host.setMQTTCallback(mqttCallback);

    gateway.toNode.setPins(SCK_PIN, MISO_PIN, MOSI_PIN, SS_PIN, RST_PIN, DIO0_PIN);
    gateway.toNode.setFrequency(LoRa_Freq);
    gateway.toNode.beginLoRa();
    
    if (!gateway.toNode.isLoRaBegan()) {
        Serial.println("device LoRa failed to begin, please restart");
        while (1); // loop for nothing
    }
    
}

void loop() {
    // Connecting to broker MQTT
    if (!gateway.host.isMQTTConnected()) {
        Serial.println("connecting to mqtt broker");
        gateway.host.connectMQTT(device_id);
        gateway.host.subscribeMQTT((mqtt_topic + "#").c_str());
    }
    gateway.host.loopMQTT();

    // LoRa receive
    String message = gateway.toNode.readMessage();
    if (message != "" && message.substring(0, 9) == String(sensor_id) + "/data/") {
        message.replace(String(sensor_id) + "/data/", "");
        gateway.host.publishMQTT((mqtt_topic + "data").c_str(), message.c_str());
    }
    gateway.toNode.loop();

    // Requesting data from host page
    if (gateway.isRequestingData()) {
        gateway.host.publishMQTT((mqtt_topic + "request").c_str(), "1");
        gateway.doneRequest();
    }
}

void mqttCallback(String topic, byte* _payload, unsigned int _length) {
    String payload = "";
    for (int i = 0; i < _length; i++)
        payload += (char)_payload[i];

    topic.replace(mqtt_topic, "");

    if (topic == "data") {
        gateway.putData(payload);
        Serial.println("sensor data: " + payload);
    }

    if (topic == "request") {
        gateway.toNode.sendMessage(String(device_id) + "/request");
        Serial.println("request sent");
    }
}