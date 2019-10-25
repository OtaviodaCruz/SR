int URPWM = 3;                   // PWM Output 0-25000us,every 50us represent 1cm
int URTRIG = 5;                   // PWM trigger pin
int indiceTempoDistancia = 18;
int distancia = 0;
int Frente = 1;

int MotorEsq = 1;
unsigned int Distance = 0;
uint8_t EnPwmCmd[4] = {0x44, 0x22, 0xbb, 0x01};

//motor A conecte na porta AO1 e AO2 do driver


//Conecte a bateria, polo positivo na porta VMOT do driver,
//e o polo negativo no GND próximo ao VMOT

//Conecte os 5 volts do Arduíno na porta VCC do driver
// e o GND do Arduíno conecte na porta GND próximo ao VCC

int STBY = 10; //ligue na standby do driver
//Motor A
int PWMA = 6; //ligue na porta PWMA do driver // Speed control
int AIN1 = 8; //ligue na porta AIN1 do driver // Direction
int AIN2 = 7; //ligue na porta AIN2 do driver Direction


void setup() {
  Serial.begin(9600);
  PWM_Mode_Setup();
  pinMode(STBY, OUTPUT);
  pinMode(PWMA, OUTPUT);
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  move(MotorEsq, 255, Frente);
  delay(3000);
}

void loop() {
  for (int i = 0; i < 20; i++) {
    move(MotorEsq, 255, Frente); //motor 1, full speed, left
    delay(100);
    distancia = PWM_Mode();
    Serial.println(distancia);

  }
}
void move(int motor, int speed, int direction) {
  //Move specific motor at speed and direction
  //speed: 0 is off, and 255 is full speed
  //direction: 0 clockwise, 1 counter-clockwise
  digitalWrite(STBY, HIGH); //disable standby
  boolean inPin1 = LOW;
  boolean inPin2 = HIGH;
  if (direction == 1) {
    inPin1 = HIGH;
    inPin2 = LOW;
  }
  if (motor == 1) {
    digitalWrite(AIN1, inPin1);
    digitalWrite(AIN2, inPin2);
    analogWrite(PWMA, speed);
  } 
}
void stop() {
  //enable standby
  digitalWrite(STBY, LOW);
}
void PWM_Mode_Setup() {
  pinMode(URTRIG, OUTPUT);              // A low pull on pin COMP/TRIG
  digitalWrite(URTRIG, HIGH);            // Set to HIGH
  pinMode(URPWM, INPUT);               // Sending Enable PWM mode command
  for (int i = 0; i < 4; i++) {
    Serial.write(EnPwmCmd[i]);
  }
}
int PWM_Mode() {                  // a low pull on pin COMP/TRIG triggering a sensor reading
  digitalWrite(URTRIG, LOW);
  digitalWrite(URTRIG, HIGH);           // reading Pin PWM will output pulses
  unsigned long DistanceMeasured = pulseIn(URPWM, LOW);
  if (DistanceMeasured == 50000) {         // the reading is invalid.
    Serial.print("Invalid");
  }
  else {
    Distance = DistanceMeasured / 50;       // every 50us low level stands for 1cm
  }
  return Distance;
}
