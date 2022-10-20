/**
 * Data sensor device "Sensor Node"
 */
#define APP_VERSION "0.1"

// Configuration
#define gateway_id  "gateway01"
#define sensor_id   "s01"
#define LoRa_Freq   923E6

// LoRa pinouts
#define SCK_PIN     5
#define MISO_PIN    19
#define MOSI_PIN    27
#define SS_PIN      18
#define RST_PIN     14
#define DIO0_PIN    26

#include <Arduino.h>
#include "gateway.h"

void setup() {
    Serial.begin(9600);
    Serial.println();

    gateway.toNode.setPins(SCK_PIN, MISO_PIN, MOSI_PIN, SS_PIN, RST_PIN, DIO0_PIN);
    gateway.toNode.setFrequency(LoRa_Freq);
    gateway.toNode.beginLoRa();
    Serial.println(gateway.toNode.isLoRaBegan());
}

void loop() {
    String hasil = gateway.toNode.readMessage();
    if (hasil != "" && hasil.substring(0, 9) == String(gateway_id)) {
        gateway.toNode.sendMessage(String(sensor_id) + "/data/" + String(random(0, 1000)));
        Serial.println("sending data");
    }
    gateway.toNode.loop();
}
