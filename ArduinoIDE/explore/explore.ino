// Bit-intervall i mikrosekund:
int Tb_mus = 1000;
// Bitmønster:
bool outBits[] = {1, 1, 1, 1, 0, 0, 0, 0,
1, 1, 1, 0, 0, 0, 1, 0,
1, 0, 1, 0, 1, 0, 1, 0};
bool inBit = 0;
bool hit = 0;
int i = 0;
int outputPin = 13;
int inputPin = 12;
int outputRedPin = 9;
void setup() {
  pinMode(inputPin, INPUT);
  pinMode(outputPin, OUTPUT);
  pinMode(outputRedPin, OUTPUT);
}
void loop() {
  digitalWrite(outputPin, outBits[i]);
  delayMicroseconds(Tb_mus/2);
  inBit = digitalRead(inputPin);
  hit = (inBit == outBits[i]);
  digitalWrite(outputRedPin, !hit);
  delayMicroseconds(Tb_mus/2);
  i += 1;
  if (i > (int(sizeof(outBits))-1)) {
    i = 0;
  }
}