#include "Motor.h" // Import classe Motor.h, que deve estar na mesma pasta deste arquivo .ino

Motor *motor1;
Motor *motor2;

#define DANCE_BUTTON 8    // Ignorar. Apenas funcao extra
#define LD_BUTTON 7       // Botão liga-desliga do sistema
#define FR_BUTTON 6       // Botão frei magnético do sistema
#define POT_V A1          // Pino de leitura da tensão no potenciometro

//Variaveis para debouncing do LD_BUTTON
bool chButtonState, lastChButtonState = 0;
unsigned long lastDeboucingTime = 0, debounceDelay = 50;
bool estadoSistema = 1;
bool teste;

void setup() {
  /* Informações da classe motor*/
  // Cria um objeto 'motor' da classe 'Motor' e inicializacao dos pinos Motor(IN1, IN2, ENABLE);
  motor1 = new Motor(4, 5, 3);
  motor2 = new Motor(8, 7, 9);

  pinMode(motor1->getIN1(), OUTPUT);     // Configuracao do pino IN1 como OUTPUT
  pinMode(motor1->getIN2(), OUTPUT);     // Configuracao do pino IN2 como OUTPUT
  pinMode(motor1->getEnable(), OUTPUT);  // Configuracao do pino ENABLE como OUTPUT
  
  pinMode(motor2->getIN1(), OUTPUT);     // Configuracao do pino IN1 como OUTPUT
  pinMode(motor2->getIN2(), OUTPUT);     // Configuracao do pino IN2 como OUTPUT
  pinMode(motor2->getEnable(), OUTPUT);  // Configuracao do pino ENABLE como OUTPUT
  
  //Variáveis internas do programa (botoes)
  pinMode(LD_BUTTON, INPUT_PULLUP);     // Configuracao do pino LD_BUTTON como INPUT_PULLUP
  pinMode(FR_BUTTON, INPUT_PULLUP);     // Configuracao do pino FR_BUTTON como INPUT_PULLUP

  Serial.begin(9600);                   // Inicializacao da porta serial
  Serial.println(" -------- PROGRAMA EM FUNCIONAMENTO -------- ");
}

void loop() {
  float f_tensao = calculaTensao();       // Chamada da funcao para calculo da tensao no potenc.
  //Ativa o freio mag. se o motor estiver funcionando e a chave FR_BUTTON pressionada
  //if (!digitalRead(FR_BUTTON) && ligaDesliga()) {
    //motor->stopMotor(f_tensao);          // Metodo do objeto 'motor' para freio magnetico
  //} else      // Operador ternario
    // Se o sistema estiver ligado, faz o motor funcionar. Caso contrario, desliga motor.
    //ligaDesliga() ? motor1->rodaMotor(f_tensao) : motor->desligaMotor();
    motor1->rodaMotor(f_tensao);
    motor2->rodaMotor(f_tensao);
  //Serial.println(ligaDesliga());
}

float calculaTensao() {  // funcao para calculo da tensao no potenc.
  return analogRead(POT_V);
}

bool ligaDesliga() { // Debounce do botao liga desliga. Retorna 1 para ligado, 0 para desligado.
  // Ver referencia em https://www.arduino.cc/en/Tutorial/Debounce para entendimento da funcao
  int chReading = !digitalRead(LD_BUTTON);
  if (chReading != lastChButtonState) {
    lastDeboucingTime = millis();
  }

  if ((millis() - lastDeboucingTime) > debounceDelay) {
    if (chReading != chButtonState) {
      chButtonState = chReading;
      if (chButtonState) {
        estadoSistema = !estadoSistema;
      }
    }
  }
  lastChButtonState = chReading;
  return estadoSistema;
}

