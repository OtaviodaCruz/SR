//PID constants
double kp = 1;
double ki = 1;
double kd = 1;
unsigned long tempoAgora , tempoAnterior;
double tempoPassou;
double erro;
double erroUltimo=0;
float input,output, setPoint, temporaria;
double erroAcumulado, erroTaxa;


const unsigned int TRIG_PIN=16;
const unsigned int ECHO_PIN=5;
const unsigned int BAUD_RATE=115200;
const unsigned int temp = 24;
const unsigned int umi = 63;
float distance;
void setup(){
  setPoint = 0;
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  Serial.begin(BAUD_RATE);
}
void loop(){
if(Serial.available ()>0){
  temporaria = Serial.parseFloat();
  if(temporaria!=0){
    setPoint = temporaria;
    }
  }
input = ultrasson();// ler sensor
output = calcularPID(input); // aplicar saída do PID no atuador
delay(1000);
//analogWrite(3, output);
print();
}
float calcularPID (float inp){
tempoAgora = millis();
tempoPassou = (double) ((tempoAgora - tempoAnterior)/1000);
erro = setPoint - input;
erroAcumulado += (erro * tempoPassou);
erroTaxa = (erro - erroUltimo)/ tempoPassou;
Serial.println(tempoPassou);
Serial.println(erroUltimo);
float out =  kp*erro + ki* erroAcumulado + kd*erroTaxa ;//PID output
Serial.println(erro);
Serial.println(erroAcumulado);
Serial.println(erroTaxa);

erroUltimo = erro ;//lembrar o erro atual
tempoAnterior = tempoAgora ;//lembrar o tempo atual
return out;
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
   Serial.println("Warning: no pulse from sensor");
   } 

return distance;
  }

  void print(){
      Serial.print("distance to nearest object: ");
      Serial.print(distance);
      Serial.println(" cm");
      Serial.print("Saida ");
      Serial.println(output);
      Serial.print("Nível d'água desejado ");
      Serial.println(setPoint);

    
    }
