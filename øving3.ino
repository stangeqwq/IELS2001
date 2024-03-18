#include <Deploii_ESP32.h>

Deploii oi; //lager en "instans"/objekt av biblioteket

const char ssid[] = "NTNU-IOT";  //Sett inn nettverksnavn her
const char passord[] = "";  //Sett inn nettverkspassord her
const char kortID[] = "EbMnsADQIJ9bOYhh89QM";  //Sett inn Kort-ID her

const int LED = 16;
const int POTENTIO_PIN1 = 32;
const int POTENTIO_PIN2 = 26;

int freq = 2000;
int channel = 0;
int resolution = 8;

void setup() {
  Serial.begin(9600);
  pinMode(LED, OUTPUT); //setter opp et LED-lys på pin 33
  pinMode(POTENTIO_PIN1, INPUT);
  //
  oi.oppkobling(ssid, passord, kortID); //kobler opp til Deploii-nettsiden
}

void sendData() { //Sender data fra kort til nettsiden
  float data = analogRead(POTENTIO_PIN1);
  oi.send("potentio_1", data); //Biblioteksfunksjon som sender data

  float data2 = data+50.0;
  oi.send("potentio_2", data2); //Biblioteksfunksjon som sender data

  float data_array[] = {2300.0, 2000.0, 3000.0};
  String text = "Hello World";
  float tall = 500.0;
  oi.send("data_1", tall);
  oi.send("potentio_3", data2+50.0);
}

void mottaData(String modulID, String data) { //Får data fra nettsiden
  //Reager på kontrollpanelmodulene
  if (modulID == "tastatur") { //reagerer på kontrollpanelmodulen tastaturstyring
    if (data == "W") { //Skrur LED på om "W" trykkes på nettsiden
      digitalWrite(LED, HIGH); 
    }

    if (data == "S") { //Skrur LED av om "S" trykkes på nettsiden
      digitalWrite(LED, LOW);
    }
  }
  if (modulID == "data") {
    Serial.println(data);
    if (data == "lyssa") {
      digitalWrite(LED, HIGH);
    }

  }
  if (modulID == "knapper") {
    Serial.println(data);
    if (data == "1") {
      digitalWrite(LED, HIGH);
    }
    if (data == "2") {
      digitalWrite(LED, LOW);
    }
  }
  if (modulID == "<<d_day>>") {
    if (data == "0") {
      digitalWrite(LED, HIGH);
    } else {
      digitalWrite(LED, LOW);
    }
  }
}

void loop() {
  oi.loop(); //Holder oppkoblingen til serveren gående
  /* OBS! OBS! Det er veldig viktig at det ikke brukes delay noen som helst sted i koden.
  Delay vil bryte opp koblingen mellom mikrokontrolleren og nettsiden. 
  Bruk oi.intervall() funksjonen for å lage repeternde hendelser istedenfor.
  */
  //Serial.println(analogRead(POTENTIO_PIN1));
  //Serial.println(analogRead(POTENTIO_PIN2));
  //Serial.println("Sending data in 2 sec");
  oi.hentDag()
  oi.intervall(2000, sendData); // Kaller sendData funksjonen hvert andre sekund
  //Serial.println("Sent!");
}