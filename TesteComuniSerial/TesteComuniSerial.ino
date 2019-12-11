void setup() {
  Serial.begin(9600);
}

void loop() {
//Serial.write('A');
// delay(2000);
 if(Serial.available()>0){
 char c = Serial.read();
 Serial.println(c);
 }
 delay(100);
// }

}
