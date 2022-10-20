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
    bool isRequestingData();
    void doneRequest();

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

    class hostClass {
        private:
        String datanya = "0";

        public:
        void initHost();
        void connectWiFi(const char* id, const char* pw);
        IPAddress getHostAddress();
        void sendData(String data);
        void setMQTTBroker(const char* mqtt_broker, uint16_t mqtt_port);
        void setMQTTCallback(std::function<void(char*, uint8_t*, unsigned int)> callback);
        bool connectMQTT(const char *mqtt_id, const char *mqtt_user, const char *mqtt_pass);
        bool connectMQTT(const char *mqtt_id);
        void subscribeMQTT(const char *topic);
        void publishMQTT(const char *topic, const char* payload);
        bool isMQTTConnected();
        void loopMQTT();
    }; hostClass host;

};

extern gatewayClass gateway;

#endif