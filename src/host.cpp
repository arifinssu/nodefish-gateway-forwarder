#include "gateway.h"
#include "pages.h"
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <PubSubClient.h>

WiFiClient client;
AsyncWebServer web(80);
PubSubClient mqtt(client);

String getIndexValues(const String &vars) {
    if (vars == "data_stored") return gateway.getData();
    return String();
}

void gatewayClass::hostClass::initHost() {
    web.on("/style.css", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send(200, "text/css", style_css);
    });

    web.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send_P(200, "text/html", index_html, getIndexValues);
    });

    web.on("/getData", HTTP_GET, [](AsyncWebServerRequest *request) {
        AsyncWebServerResponse *response = request->beginResponse(200, "text/html", "<meta http-equiv=\"refresh\" content=\"1; url=/\"> getting sensor data...");
        request->send(response);
        gateway.requestData = true;
    });

    web.onNotFound([](AsyncWebServerRequest *request) {
        request->send(404);
    });

    web.begin();
}

void gatewayClass::hostClass::connectWiFi(const char* id, const char* pw) {
    WiFi.disconnect();
    WiFi.mode(WIFI_STA);
    WiFi.begin(id, pw);
    while (WiFi.status() != WL_CONNECTED);
}

IPAddress gatewayClass::hostClass::getHostAddress() {
    return WiFi.localIP();
}

void gatewayClass::hostClass::sendData(String data) {
    datanya = data;
}

void gatewayClass::hostClass::setMQTTBroker(const char* mqtt_broker, uint16_t mqtt_port) {
    mqtt.setServer(mqtt_broker, mqtt_port);
}

void gatewayClass::hostClass::setMQTTCallback(std::function<void(char*, uint8_t*, unsigned int)> callback) {
    mqtt.setCallback(callback);
}

bool gatewayClass::hostClass::connectMQTT(const char *mqtt_id, const char *mqtt_user, const char *mqtt_pass) {
    return mqtt.connect(mqtt_id, mqtt_user, mqtt_pass);
}

bool gatewayClass::hostClass::connectMQTT(const char *mqtt_id) {
    return mqtt.connect(mqtt_id);
}

void gatewayClass::hostClass::subscribeMQTT(const char *topic) {
    mqtt.subscribe(topic);
}

void gatewayClass::hostClass::publishMQTT(const char *topic, const char* payload) {
    mqtt.publish(topic, payload);
}

bool gatewayClass::hostClass::isMQTTConnected() {
    return mqtt.connected();
}

void gatewayClass::hostClass::loopMQTT() {
    mqtt.loop();
}