#include "Deploii_ESP32.h"

/*Global variables*/
//Incoming JSON data
const int inCapacity = JSON_OBJECT_SIZE(100);
DynamicJsonDocument inMsgs(inCapacity);

//Outgoing JSON data
const int outCapacity = JSON_OBJECT_SIZE(20);
StaticJsonDocument<outCapacity> outMsgs;

//Main setup
Deploii::Deploii() {

}

void Deploii::intervall(int intervall, std::function<void()> callback) {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= intervall) {
    previousMillis = currentMillis;
    callback();
  }
}

void Deploii::auth() {
  outMsgs.clear();
  outMsgs["t"] = 1;
  outMsgs["mcuID"] = _mcuID;
  char out_msg[50];
  serializeJson(outMsgs, out_msg); 
  ws.sendTXT(out_msg);
}

void Deploii::receive(const char* dataID, const char* data, std::function<void(String, String)> callback) {
  callback(String(dataID), String(data));
}

void Deploii::processPayload(unsigned char* payload, size_t length) {
  char payloadData[length];

  //Converting from unsigned to "regular" char
  for (int i = 0; i < length; i++) {
    payloadData[i] = (char)payload[i];
  }

  //Deserialize data (JSON.parse)
  err = deserializeJson(inMsgs, payloadData, length);

  if (err) {
    Serial.print(F("deserializeJson() failed with code "));
    Serial.println(err.f_str());
  }

  //Perform actions based on msg type from server
  msgType = inMsgs["t"];

  //Perform actions based on incoming commands
  dataID = inMsgs["b"]["dID"];
  data = inMsgs["b"]["d"];

  switch (msgType) {
    case 1: //Authentication granted
      Serial.println("[Deploii] Gyldig Brett-ID.");
    break;

    case 2: //Authentication not granted
      Serial.println("[Deploii] Brett-ID er ikke gyldig. Du må legge inn en annen Brett-ID.");
    break;

    case 4: //Data sent from server
      if (mottaData) {
        receive(dataID, data, mottaData);
      }
    break;

    case 5: //Ping sent from server
      outMsgs.clear();
      outMsgs["t"] = 6; 
      char out_msg[12];
      serializeJson(outMsgs, out_msg); 
      ws.sendTXT(out_msg); //Send pong back
    break;

    default:
      Serial.println("Not a valid msg type.");
      Serial.println(msgType);
    break;
  }
}

void Deploii::setupWebSocket(WStype_t type, unsigned char* payload, size_t length) {
  switch(type) { //WS msg type
    case WStype_DISCONNECTED:
      Serial.println("[Deploii] Disconnected.");
    break;

    case WStype_CONNECTED:
      Serial.println("[Deploii] Sikker kobling til Deploii-skyen etablert.");
      auth();
    break;

    case WStype_TEXT:
      //Debug
      //Serial.printf("received text data: %s\n", payload);

      //Process the data and call actions
      processPayload(payload, length);
    break;

    case WStype_BIN:
      //Serial.println("[Deploii] binary data received:");
    break;

    case WStype_ERROR:			
      //Serial.println("Some WebSocket error");
    break;
  }
}

/* Start send-functions */
void Deploii::send(char* dataID, float data) {
  outMsgs.clear();
  outMsgs["t"] = 3;
  outMsgs["sub_t"] = 1;
  outMsgs["dID"] = dataID;
  outMsgs["d"] = data;
  char out_msg[75];
  serializeJson(outMsgs, out_msg);
  ws.sendTXT(out_msg);
}

void Deploii::send(char* dataID, float data[], int len, int option) {
  StaticJsonDocument<JSON_ARRAY_SIZE(10)> docSend;
  JsonArray dataArr = docSend.to<JsonArray>();

  for(int i = 0; i < len; i++) {
    dataArr.add(data[i]);
  }

  outMsgs.clear();
  outMsgs["t"] = 3;
  outMsgs["sub_t"] = 1;
  outMsgs["dID"] = dataID;
  outMsgs["d"] = docSend;
  outMsgs["o"] = option;
  char out_msg[150];
  serializeJson(outMsgs, out_msg);
  ws.sendTXT(out_msg);
}

void Deploii::send(char* dataID, char* data) {
  outMsgs.clear();
  outMsgs["t"] = 3;
  outMsgs["sub_t"] = 1;
  outMsgs["dID"] = dataID;
  outMsgs["d"] = data;
  char out_msg[200];
  serializeJson(outMsgs, out_msg);
  ws.sendTXT(out_msg);
}

void Deploii::send(char* dataID, String data) {
  outMsgs.clear();
  outMsgs["t"] = 3;
  outMsgs["sub_t"] = 1;
  outMsgs["dID"] = dataID;
  outMsgs["d"] = data;
  char out_msg[200];
  serializeJson(outMsgs, out_msg);
  ws.sendTXT(out_msg);
}
/* End send-functions */

/* Start other user functions */
void Deploii::hentTid(int option) {
  outMsgs.clear();
  outMsgs["t"] = 3;
  outMsgs["sub_t"] = 2;
  outMsgs["o"] = option;
  char out_msg[25];
  serializeJson(outMsgs, out_msg);
  ws.sendTXT(out_msg);
}

void Deploii::hentDato(int option) {
  outMsgs.clear();
  outMsgs["t"] = 3;
  outMsgs["sub_t"] = 3;
  outMsgs["o"] = option;
  char out_msg[25];
  serializeJson(outMsgs, out_msg);
  ws.sendTXT(out_msg);
}

void Deploii::hentDag() {
  outMsgs.clear();
  outMsgs["t"] = 3;
  outMsgs["sub_t"] = 4;
  char out_msg[25];
  serializeJson(outMsgs, out_msg);
  ws.sendTXT(out_msg);
}
/* End other user functions */

void Deploii::oppkobling(const char* ssid, const char* password, const char* mcuID) {
  _mcuID = mcuID;

  Serial.println();
  Serial.println();

  Serial.println(" 11111111   11111111  11111111   11        1111111    00    00  ");
  Serial.println(" 11     11  11        11     11  11       11     11  0  0--0  0 ");
  Serial.println(" 11     11  11        11     11  11       11     11   00    00  ");
  Serial.println(" 11     11  111111    11111111   11       11     11   11    11  ");
  Serial.println(" 11     11  11        11         11       11     11   11    11  ");
  Serial.println(" 11     11  11        11         11       11     11   11    11  ");
  Serial.println(" 11111111   11111111  11         11111111  1111111    11    11 ");
  Serial.println();

  WiFi.begin(ssid, password);
  WiFi.setSleep(WIFI_PS_NONE); //Set sleep mode to none, to improve latency/performance

  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
  }
  Serial.println("[Deploii] Koblet til Wi-Fi.");
  Serial.print("[Deploii] Lokal IP-address er ");
  Serial.print(WiFi.localIP());
  Serial.println(".");
  Serial.println();

  ws.beginSSL(serverMainIP , serverMainPort, serverMainRoute);
  ws.onEvent(std::bind(&Deploii::setupWebSocket, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
  ws.setReconnectInterval(2500); //this should probably be a random function to avoid DoS at server restart

  delay(1000);
}

void Deploii::loop() {
  ws.loop();
}