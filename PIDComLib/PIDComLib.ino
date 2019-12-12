#include <PID_v1.h>
//Em cm
#define DISTANCIA_MAX 30
//Direção de funcionamento do motor.
int STBY = 10; //ligue na standby do driver
int PWMA = 6; //ligue na porta PWMA do driver // Speed control
int AIN1 = 8; //ligue na porta AIN1 do driver // Direction
int AIN2 = 7; //ligue na porta AIN2 do driver Direction
//Direção de funcionamento do motor.
int Frente = 1;
//ultrassonico
const unsigned int TRIG_PIN=5;
const unsigned int ECHO_PIN=4;
const unsigned int BAUD_RATE=115200;
const unsigned int temp = 24;
const unsigned int umi = 63;
float distance;


// Define Variables we'll be connecting to
double Setpoint, Input, Output;
// Specify the links and initial tuning parameters
double Kp =1, Ki=1, Kd =1;
PID myPID(&Input, &Output, &Setpoint, Kp, Ki, Kd, DIRECT);
void setup()
{
  pinMode(STBY, OUTPUT);
  pinMode(PWMA, OUTPUT);
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
// initialize the variables we're linked to
Input = ultrasson();
Setpoint = 0;
// turn the PID on
myPID.SetMode(AUTOMATIC);

//Se eu quisesse limitar via lib PID
//double Min = 0;
//double Max = 256;
//myPID.SetOutputLimits( Min,  Max);
//Amostragem em segundos
myPID.SetSampleTime(0.5);
delay(1500);
}void loop()
{
Input = ultrasson();
myPID.Compute();
//analogWrite(PIN_OUTPUT, Output);
}
float ultrasson(){
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
distance = (duration/2) *(velocidade/10000);
 if(duration==0){
   Serial.println("Nenhum pulso");
   } 
   if(distance > DISTANCIA_MAX ){
    distance = DISTANCIA_MAX;
    
    }
return distance;
  }

  void print(){
      Serial.print("Distância medida: ");
      Serial.print(distance);
      Serial.println(" cm");
      Serial.print("Nível d'água desejado: ");
      Serial.println(Setpoint);
      Serial.print("Saida: ");
      Serial.println(Output);
      Serial.print("PWM: ");
      //Serial.println(speed);
      
    }
    void move(int speed) {
    //Controle da saturação
    if(speed<0){
      Serial.println("Speed < 0");
      speed = 0;
      }
      if(speed>255){
        Serial.println("Speed > 255");
        speed = 255;
        }
  //Move specific motor at speed and direction
  //speed: 0 is off, and 255 is full speed
  //direction: 0 clockwise, 1 counter-clockwise
  digitalWrite(STBY, HIGH); //disable standby
  //Seta variáveis para o sentido de rotação
  //PWM e sentido de rotação do motor setados. Deve ter o motor funcionando conforme
  //os parâmetros

    digitalWrite(AIN1, HIGH);
    digitalWrite(AIN2, LOW);
    analogWrite(PWMA, speed);
  }
