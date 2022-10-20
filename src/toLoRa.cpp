#include "gateway.h"
#include <SPI.h>
#include <LoRa.h>

void gatewayClass::toLoRaClass::getMessage() {
    for (int i = 0; i < incomingPacketSize; i++)
    message += (char)LoRa.read();

    rssi = LoRa.packetRssi();
}

void gatewayClass::toLoRaClass::receiveMode() {
    LoRa.disableInvertIQ();
    LoRa.receive();
}

void gatewayClass::toLoRaClass::transmitMode() {
    LoRa.idle();
    LoRa.enableInvertIQ();
}

void gatewayClass::toLoRaClass::setPins(int sck, int miso, int mosi, int ss, int rst, int dio0) {
    _sck = sck;
    _miso = miso;
    _mosi = mosi;
    _ss = ss;
    _rst = rst;
    _dio0 = dio0;
}

void gatewayClass::toLoRaClass::setFrequency(double freq) {
    _freq = freq;
}

void gatewayClass::toLoRaClass::beginLoRa() {
    SPI.begin(_sck, _miso, _mosi, _ss);
    LoRa.setPins(_ss, _rst, _dio0);

    if (!LoRa.begin(_freq)) 
        beganLoRa = false;

    LoRa.onReceive(gateway.toNode.onReceive);
    beganLoRa = true;

    receiveMode();
}

bool gatewayClass::toLoRaClass::isLoRaBegan() {
    return beganLoRa;
}

void gatewayClass::toLoRaClass::sendMessage(String message) {
    transmitMode();
    LoRa.beginPacket();
    LoRa.print(message);
    LoRa.endPacket(true);
    receiveMode();
}

String gatewayClass::toLoRaClass::readMessage() {
    if (message == "") return "";

    String result = message;
    message = "";
    return result;
}

void gatewayClass::toLoRaClass::loop() {
    if (!beganLoRa) return;
    if (incomingData) {
        message = "";
        getMessage();
        incomingData = false;
    }
}

void gatewayClass::toLoRaClass::onReceive(int packetSize) {
    gateway.toNode.incomingData = true;
    gateway.toNode.incomingPacketSize = packetSize;
}