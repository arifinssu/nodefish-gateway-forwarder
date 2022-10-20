/**
 * Main device "Forwarder Node"
 */
#define APP_VERSION "0.1"

// Configuration
#define device_id   "gateway01"
#define sensor_id   "s01"
#define ssid        "Narnia"
#define pass        "cumamintadoang"
#define broker      "147.139.139.55"
#define broker_port 5883
#define LoRa_Freq   923E6

// LoRa pinouts
#define SCK_PIN     5
#define MISO_PIN    19
#define MOSI_PIN    27
#define SS_PIN      18
#define RST_PIN     23
#define DIO0_PIN    26

#include <Arduino.h>
#include "gateway.h"

void setup() {
    Serial.begin(9600);
    Serial.println();

    gateway.toNode.setPins(SCK_PIN, MISO_PIN, MOSI_PIN, SS_PIN, RST_PIN, DIO0_PIN);
    gateway.toNode.setFrequency(LoRa_Freq);
    gateway.toNode.beginLoRa();
    
    if (!gateway.toNode.isLoRaBegan()) {
        Serial.println("device LoRa failed to begin, please restart");
        while (1); // loop for nothing
    }
    
}

void loop() {
    // LoRa receive
    String message = gateway.toNode.readMessage();
    if (message != "" && message.substring(0, 9) == String(sensor_id) + "/data/") {
        message.replace(String(sensor_id) + "/data/", "");
        gateway.putData(message);
    }
    gateway.toNode.loop();
}
