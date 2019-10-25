//Documentation: https://bitbucket.org/teckel12/arduino-new-ping/wiki/Home
#include <NewPing.h>
 
#define TRIG_PIN 6
#define ECHO_PIN 5 
#define DISTANCIA_MAX 100

//Declarações
//Direção de funcionamento do motor.
int Frente = 1;
//Sentido de rotação do motor.
int MotorEsq = 1;
//API utilizada para acionar o sonar
int STBY = 10; //ligue na standby do driver
int PWMA = 6; //ligue na porta PWMA do driver // Speed control
int AIN1 = 8; //ligue na porta AIN1 do driver // Direction
int AIN2 = 7; //ligue na porta AIN2 do driver Direction
//Distancia em cm
NewPing sonar(TRIG_PIN, ECHO_PIN, DISTANCIA_MAX);
//Variável para o sonar
float distancia = 0.0;
 
void setup(void) 
{
  Serial.begin(9600);
  PWM_Mode_Setup();
  pinMode(STBY, OUTPUT);
  pinMode(PWMA, OUTPUT);
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  move(MotorEsq, 255, Frente);
  delay(1500);
}
 
void loop()
{
   distancia = sonar.ping_cm();//Calculando em cm
   Serial.print("Distancia em cm:");
   Serial.println(distancia);
   //A distancia sera calculada a cada segundo
   delay(1000);
}

void move(int motor, int speed, int direction) {
  //Move specific motor at speed and direction
  //speed: 0 is off, and 255 is full speed
  //direction: 0 clockwise, 1 counter-clockwise
  digitalWrite(STBY, HIGH); //disable standby
  //Seta variáveis para o sentido de rotação
  boolean inPin1 = LOW;
  boolean inPin2 = HIGH;
  if (direction == 1) {
    inPin1 = HIGH;
    inPin2 = LOW;
  }
  //PWM e sentido de rotação do motor setados. Deve ter o motor funcionando conforme
  //os parâmetros
  if (motor == 1) {
    digitalWrite(AIN1, inPin1);
    digitalWrite(AIN2, inPin2);
    analogWrite(PWMA, speed);
  } 
}
