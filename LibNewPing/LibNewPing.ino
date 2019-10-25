//Documentation: https://bitbucket.org/teckel12/arduino-new-ping/wiki/Home
#include <NewPing.h>
 
#define TRIG_PIN 6
#define ECHO_PIN 5 
#define DISTANCIA_MAX 100
//API utilizada para acionar o sonar
NewPing sonar(TRIG_PIN, ECHO_PIN, DISTANCIA_MAX);//Distancia em cm
 
float distancia = 0.0;
 
void setup(void) 
{
  Serial.begin(9600);
}
 
void loop()
{
   //distancia = sonar.ping()/US_ROUNDTRIP_CM;//Calculando em cm
   distancia = sonar.ping_cm();//Calculando em cm
   Serial.print("Distancia em cm:");
   Serial.println(distancia);
   delay(1000);//A distancia sera calculada a cada segundo
}
