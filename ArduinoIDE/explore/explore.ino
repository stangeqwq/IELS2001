
int freq = 1;
void setup(){

}
void loop(){
  dacWrite(25, 1);
  delay((1 / 2*freq) * 1000);
  dacWrite(25, 0);
  delay((1 / 2*freq) * 1000);
}