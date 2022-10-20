# Nodefish Gateway Forwarder
Here is Forwarder Node that acts as an intermediary for offline Sensor Nodes, and the cloud. Communication between Forwarder Node and Sensor Nodes are via a wireless protocol.

## How to use?
- Download or clone this repo to your own computer
- Look for `node.cpp` to program the sensor device and `main.cpp` as gateway forwarder device
- Edit the configuration and LoRa pinouts below according to yours

```cpp
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
#define RST_PIN     14
#define DIO0_PIN    26
```

- Now compile and upload the firmware according to platformio .env

## API reference

#### Class Parent
- gateway

#### Class Childs
- toNode (Gateway to Node Functions)
- host (Gateway Host Functions)

_______________________________

#### Gateway to Node Functions (toNode)
- void setPins(int sck, int miso, int mosi, int ss, int rst, int dio0);

| Parameters | Description |
| ------------- | ------------------------------ |
| `sck` int | LoRa SCK_PIN |
| `miso` int | LoRa MISO_PIN |
| `mosi` int | LoRa MOSI_PIN |
| `ss` int | LoRa CS_PIN |
| `rst` int | LoRa RST_PIN |
| `dio0` int | LoRa DIO0_PIN |

- void setFrequency(double freq);

| Parameters | Description |
| ------------- | ------------------------------ |
| `freq` double | LoRa Frequency |

- void beginLoRa();

Begin LoRa

- bool isLoRaBegan();

Check if LoRa has began

- void sendMessage(String message);

| Parameters | Description |
| ------------- | ------------------------------ |
| `message` String | LoRa payload message |

- String readMessage();

Return LoRa payload from another LoRa device

- void loop();

Needs to looping the process of toNode child class

_______________________________

#### Gateway Host Functions (host)
- void initHost();

Setup the WebHost (async) for local gateway server

- void connectWiFi(const char* id, const char* pw);

| Parameters | Description |
| ------------- | ------------------------------ |
| `id` const char* | WiFi SSID |
| `pw` const char* | WiFi SSID Password |

- IPAddress getHostAddress();

Get the host IPAddress to be access from another client device (pc / handphone)

- void sendData(String data);

| Parameters | Description |
| ------------- | ------------------------------ |
| `data` String | Data from payload |

- void setMQTTBroker(const char* mqtt_broker, uint16_t mqtt_port);

| Parameters | Description |
| ------------- | ------------------------------ |
| `mqtt_broker` const char* | Broker MQTT Address |
| `mqtt_port` const char* | Broker MQTT Port |

- void setMQTTCallback(std::function<void(char*, uint8_t*, unsigned int)> callback);

| Parameters | Description |
| ------------- | ------------------------------ |
| `callback` void* | MQTT Callback |

- bool connectMQTT(const char *mqtt_id, const char *mqtt_user, const char *mqtt_pass);

| Parameters | Description |
| ------------- | ------------------------------ |
| `mqtt_id` const char* | MQTT Device ID |
| `mqtt_user` const char* | MQTT Broker Username (if any) |
| `mqtt_pass` const char* | MQTT Broker Password (if any) |

- bool connectMQTT(const char *mqtt_id);

| Parameters | Description |
| ------------- | ------------------------------ |
| `mqtt_id` const char* | MQTT Device ID |

- void subscribeMQTT(const char *topic);

| Parameters | Description |
| ------------- | ------------------------------ |
| `topic` const char* | Subscribe to MQTT topic |

- void publishMQTT(const char *topic, const char* payload);

| Parameters | Description |
| ------------- | ------------------------------ |
| `topic` const char* | MQTT topic to publish |
| `payload` const char* | MQTT payload to fill to the topic |

- bool isMQTTConnected();

Check if device connected to MQTT Broker

- void loopMQTT();

Needed to loop MQTT process (embed from PubSubClient lib)

## Library Dependencies
- [LoRa](https://github.com/sandeepmistry/arduino-LoRa)
- [ESP Async WebServer](https://github.com/me-no-dev/ESPAsyncWebServer)
- [PubSubClient](https://github.com/knolleary/pubsubclient)