/* DOCUMENTACAO CLASSE MOTOR
 *  Classe desenvolvida por Paulo C. Silva, outubro/2017.
 *  Descricao: Classe para controle de motores utilizando o modulo l298n.
 *  Atributos: 
 *    _in1 - Pino IN1 conectado do modulo.
 *    _in2 - Pino IN2 conectado do modulo.
 *    _enable - Pino ENABLE do m�dulo.
 *    _sentido  - variavel do tipo enum para armazenamento o sentido de rotaacao 
 *                do motor.
 *    _last_time - Variavel auxiliar para funcao millis();
 *  Metodos: 
 *    getters() e setters();
 *    void rodaMotor(float f_tensao) - Inicia a rotacao de acordo com a tensao f_tensao. 
 *      - Para f_tensao = 0, motor parado.
 *      - Para f_tensao >= 3.3/2, sentido horario. 
 *      - Para f_tensao <= 3.3/2, sentido anti-horario.
 *    void dancaMotor(int tempo) - Gira motor com sentido variado e intervalo definido (tempo).
 *    void giraHorario(float tensao) - Gira motor girar em sentido horario.
 *    void giraAntiHorario(float tensao) - Gira motor girar em sentido anti-horario.
 *    void stopMotor(float tensao) - Para o motor.
 *    void desligaMotor() - Desativa (0) os pinos conectados ao madulo.
 */
enum sentido {ANTI_HORARIO, HORARIO, PARADO};

class Motor {
  private:
    int _in1;
    int _in2;
    int _enable;
    sentido _sentido;
    int _last_time; //Variavel auxiliar para a fun��o millis(), ignorar.
  public:
    Motor(int in1, int in2, int veloc);
    int getIN1(); void setIN1(int in1);
    int getIN2(); void setIN2(int in2);
    int getEnable(); void setEnable(int veloc);
    sentido getSentido(); void setSentido(sentido s);
    void rodaMotor(float f_tensao);
    void dancaMotor(float f_tensao, int tempo);
    void giraHorario(float tensao);
    void giraAntiHorario(float tensao);
    void stopMotor(float tensao);
    void desligaMotor();
};

Motor::Motor(int in1, int in2, int enable) {
  this->_in1 = in1;
  this->_in2 = in2;
  this->_enable = enable;
  this->_last_time = 0;
}

int Motor::getIN1() {
  return this->_in1;
}

int Motor::getIN2() {
  return this->_in2;
}

int Motor::getEnable() {
  return this->_enable;
}

sentido Motor::getSentido() {
  return this->_sentido;
}

void Motor::setIN1(int in1) {
  this->_in1 = in1;
}

void Motor::setIN2(int in2) {
  this->_in2 = in2;
}

void Motor::setEnable(int enable) {
  this->_enable = enable;
}
void Motor::setSentido(sentido s) {
  this->_sentido = s;
}

void Motor::giraHorario(float f_tensao) {
  int tensao = f_tensao * 100;
  int cicloPWM = map(tensao, 330 / 2, 330, 0, 255);
  setSentido(HORARIO);
  digitalWrite(getIN2(), 0);
  digitalWrite(getIN1(), 1);
  analogWrite(getEnable(), cicloPWM);
  Serial.println("-- SENTIDO HORARIO | TENSAO: " + (String) f_tensao + " V");
}

void Motor::giraAntiHorario(float f_tensao) {
  int tensao = f_tensao * 100;
  int cicloPWM = map(tensao, 0, 330 / 2, 0, 255);
  setSentido(ANTI_HORARIO);
  digitalWrite(getIN1(), 0);
  digitalWrite(getIN2(), 1);
  analogWrite(getEnable(), cicloPWM);
  Serial.println("-- SENTIDO ANTI-HORARIO | TENSAO: " + (String) f_tensao + " V");
}

void Motor::stopMotor(float f_tensao) { // Freio magn�tico do motor
  setSentido(PARADO);
  digitalWrite(getIN1(), 1);
  digitalWrite(getIN2(), 1);
  analogWrite(getEnable(), 0);
  Serial.println("-- MOTOR PARADO | TENSAO: " + (String) f_tensao + " V");
}

void Motor::rodaMotor(float f_tensao) {
  int tensao = f_tensao * 100;
  if (tensao == 330 / 2)
    stopMotor(tensao);
  else
    tensao >= 330 / 2 ? giraHorario(tensao) : giraAntiHorario(tensao);
}

void Motor::dancaMotor(float f_tensao, int tempo) {
  int tensao = f_tensao * 100;
  if (millis() - _last_time > tempo) {
    _last_time = millis();
    _sentido ? giraHorario(map(tensao, 0, 330, 165, 330)) : giraAntiHorario(map(tensao, 0, 330, 0, 165));
  }
}

void Motor::desligaMotor(){
  setSentido(PARADO);
  digitalWrite(getIN1(), 0);
  digitalWrite(getIN2(), 0);
  analogWrite(getEnable(), 0);
  Serial.println("-- MOTOR DESLIGADO ---------- ");
}
// --------------------------- FIM DA CLASSE Motor.h -----------------

//#include "Motor.h" // Import classe Motor.h, que deve estar na mesma pasta deste arquivo .ino

Motor *motor;     //

#define DANCE_BUTTON 8    // Ignorar. Apenas funcao extra
#define LD_BUTTON 7       // Botão liga-desliga do sistema
#define FR_BUTTON 6       // Botão frei magnético do sistema
#define POT_V A0          // Pino de leitura da tensão no potenciometro

//Variaveis para debouncing do LD_BUTTON
bool chButtonState, lastChButtonState = 0;
unsigned long lastDeboucingTime = 0, debounceDelay = 50;
bool estadoSistema = 1;

void setup() {
  /* Informações da classe motor*/
  // Cria um objeto 'motor' da classe 'Motor' e inicializacao dos pinos Motor(IN1, IN2, ENABLE);
  motor = new Motor(13, 12, 10);
  pinMode(motor->getIN1(), OUTPUT);     // Configuracao do pino IN1 como OUTPUT
  pinMode(motor->getIN2(), OUTPUT);     // Configuracao do pino IN2 como OUTPUT
  pinMode(motor->getEnable(), OUTPUT);  // Configuracao do pino ENABLE como OUTPUT

  //Variáveis internas do programa (botoes)
  pinMode(DANCE_BUTTON, INPUT_PULLUP);  // Configuracao do pino DANCE_BUTTON como INPUT_PULLUP
  pinMode(LD_BUTTON, INPUT_PULLUP);     // Configuracao do pino LD_BUTTON como INPUT_PULLUP
  pinMode(FR_BUTTON, INPUT_PULLUP);     // Configuracao do pino FR_BUTTON como INPUT_PULLUP

  Serial.begin(9600);                   // Inicializacao da porta serial
  Serial.println(" -------- PROGRAMA EM FUNCIONAMENTO -------- ");
}

void loop() {
  float f_tensao = calculaTensao();       // Chamada da funcao para calculo da tensao no potenc.
  //Ativa o freio mag. se o motor estiver funcionando e a chave FR_BUTTON pressionada
  if (!digitalRead(FR_BUTTON) && ligaDesliga()) {
    motor->stopMotor(f_tensao);          // Metodo do objeto 'motor' para freio magnetico
  } else      // Operador ternario
    // Se o sistema estiver ligado, faz o motor funcionar. Caso contrario, desliga motor.
    ligaDesliga() ? motor->rodaMotor(f_tensao) : motor->desligaMotor();
}

float calculaTensao() {  // funcao para calculo da tensao no potenc.
  return map(analogRead(POT_V), 0, 1023, 0, 330) / 100.0;
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

