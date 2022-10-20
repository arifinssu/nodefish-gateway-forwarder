#ifndef gateway_h
#define gateway_h

#include <Arduino.h>

class gatewayClass {
    private:
    String _data;
    bool requestData = false;

    public:
    void putData(String data);
    String getData();

    class toLoRaClass {
        private:
        int _sck, _miso, _mosi, _ss, _rst, _dio0;
        double _freq;
        bool beganLoRa = false;
        volatile bool incomingData = false;
        volatile int incomingPacketSize;
        volatile int rssi;
        String message;
        static void onReceive(int packetSize);
        void getMessage();
        void receiveMode();
        void transmitMode();

        public:
        void setPins(int sck, int miso, int mosi, int ss, int rst, int dio0);
        void setFrequency(double freq);
        void beginLoRa();
        bool isLoRaBegan();
        void sendMessage(String message);
        String readMessage();
        void loop();
    }; toLoRaClass toNode;
};

extern gatewayClass gateway;

#endif