#include "Motor.h" // Import classe Motor.h, que deve estar na mesma pasta deste arquivo .ino

Motor *motor;
#define DANCE_BUTTON 8
#define CH_BUTTON 7
#define FR_BUTTON 6
#define POT_V A0

void setup() {
  // Informações da classe motor
  motor = new Motor(13, 12, 10); // Inicialização dos pinos Motor(IN1, IN2, ENABLE);
  pinMode(motor->getIN1(), OUTPUT);
  pinMode(motor->getIN2(), OUTPUT);
  pinMode(motor->getEnable(), OUTPUT);

  //Variáveis internas do programa
  pinMode(DANCE_BUTTON, INPUT_PULLUP);
  pinMode(CH_BUTTON, INPUT_PULLUP);
  pinMode(FR_BUTTON, INPUT_PULLUP);

  Serial.begin(9600);
  Serial.println(" -------- PROGRAMA EM FUNCIONAMENTO -------- ");
}

void loop() {
  // put your main code here, to run repeatedly:
  float f_tensao = calculaTensao() / 100.0; // Tensao em decimal (0 - 3.3V);
  Serial.println("Tensao: " + (String) f_tensao + " V");
  if (!digitalRead(CH_BUTTON) && digitalRead(FR_BUTTON) || !digitalRead(FR_BUTTON)) // ISTO AQUI TÁ ERRADO VEIIIIIIIIIIIII -TEM QUE CONSERTAR 
    motor->stopMotor(f_tensao);
  else 
    !digitalRead(DANCE_BUTTON) ? motor->dancaMotor(f_tensao, 1000) : motor->rodaMotor(f_tensao); 
}

float calculaTensao() {
  return map(analogRead(POT_V), 0, 1023, 0, 330)/100.0;
}

