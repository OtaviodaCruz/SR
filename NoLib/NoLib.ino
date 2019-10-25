const unsigned int TRIG_PIN=6;
const unsigned int ECHO_PIN=5;
const unsigned int BAUD_RATE=9600;
const unsigned int temp = 24;
const unsigned int umi = 63;
void setup() {
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  Serial.begin(BAUD_RATE);
}

void loop() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  

 float duration= pulseIn(ECHO_PIN, HIGH);
 //"ritmo do som". O ritmo do som = 1 / velocidade do som = 1 / 0,03435 = 29,1 us / cm
// int distance= (duration/29.1)/2;

//spdSnd = 331.4 + (0.606 * temp) + 0.62;
float velocidade = 331.4 + (0.606 * temp) + (0.0124*umi);
float distance = (duration/2) *(velocidade/10000);
 if(duration==0){
   Serial.println("Warning: no pulse from sensor");
   } 
  else{
      Serial.print("distance to nearest object: ");
      Serial.print(distance);
      Serial.println(" cm");
      //Serial.print("temp: ");
      //Serial.println(temp);
      //Serial.print("velocidade: ");
      //Serial.println(velocidade);
      //Serial.print("umi: ");
      //Serial.println(umi);
      //Serial.print("duration: ");
      //Serial.println(duration);
  }
 delay(1000);
 }
