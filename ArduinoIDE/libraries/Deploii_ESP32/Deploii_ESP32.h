#include "Arduino.h"
#include "WiFi.h"
#include "WebSocketsClient.h"
#include <ArduinoJson.h>
#include <ArduinoJson.hpp>

class Deploii {

  public: //user library functions and variables
    Deploii();
    void oppkobling(const char* ssid, const char* password, const char* mcuID);
    void loop();
    void intervall(int intervall, std::function<void()> callback);

    //Different send functions
    void send(char* dataID, float data);
    void send(char* dataID, float data[], int len, int option = 0);
    void send(char* dataID, char* data);
    void send(char* dataID, String data);

    //Time and date functions
    void hentTid(int option = 0);
    void hentDato(int option = 0);
    void hentDag();

  private: //Internal library functions and variables
    WebSocketsClient ws;
    DeserializationError err;

    void auth();
    void setupWebSocket(WStype_t type, uint8_t * payload, size_t length);
    void processPayload(unsigned char* payload, size_t length);
    void receive(const char* dataID, const char* data, std::function<void(String, String)> callback);

    const char* serverMainIP = "deploii.no";
    const int serverMainPort = 443;
    const char* serverMainRoute = "/websocket";

    int msgType; //To read inncoming ws msg type
    const char* dataID; //To read inncoming ws storagespace
    const char* data; //To read inncoming ws data
    
    const char* _mcuID; //To store mcuID globallyawdwad

    unsigned long previousMillis = 0; //for intervall function
};

void mottaData(String modulID, String data) __attribute__ ((weak));
