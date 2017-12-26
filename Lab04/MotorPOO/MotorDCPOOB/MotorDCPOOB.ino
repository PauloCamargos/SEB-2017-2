enum sentido {HORARIO, ANTI_HORARIO, PARADO};

class Motor {
  private:
    int _pino_1;
    int _pino_2;
    int _velocidade;
    sentido  _sentido;
    float _tensao;

  public:
    Motor(int pino1, int pino2, int velocidade);
    Motor(int pino1, int pino2, sentido sens, float tensao);
    int getPino1();
    int getPino2();
    int getVelocidade();
    bool getSentido();
    float getTensao();
    void setPino1(int pino1);
    void setPino2(int pino2);
    void setVelocidade(int velocidade);
    void setSentido(sentido sens);
    void setTensao(float tensao);
    void stopMotor();
    void danceMotor(int tempo, int percTensMax, int ciclos);
    void potControle(int tensao);
};

Motor::Motor(int pino1, int pino2, int velocidade) {
  this->_pino_1 = pino1;
  this->_pino_2 = pino2;
  this->_velocidade = velocidade;
}

Motor::Motor(int pino1, int pino2, sentido sens, float tensao) {
  this->_pino_1 = pino1;
  this->_pino_2 = pino2;
  this->_sentido = sens;
  this->_tensao = tensao;
}

int Motor::getPino1() {
  return this->_pino_1;
}

int Motor::getPino2() {
  return this->_pino_2;
}

int Motor::getVelocidade() {
  return this->_velocidade;
}

bool Motor::getSentido() {
  return this->_sentido;
}

float Motor::getTensao() {
  return this->_tensao;
}

void Motor::setPino1(int pino1) {
  this->_pino_1 = pino1;
}

void Motor::setPino2(int pino2) {
  this->_pino_2 = pino2;
}

void Motor::setVelocidade(int velocidade) {
  this->_velocidade = velocidade;
}
void Motor::setSentido(sentido sens) {
  this->_sentido = sens;
}

void Motor::setTensao(float tensao) {
  this->_tensao = tensao;
}
void Motor::stopMotor() {
  analogWrite(getPino1(), 0);
  analogWrite(getPino2(), 0);
}

void Motor::danceMotor(int tempo, int percTensMax, int ciclos) {
  int volts = getTensao() * percTensMax / 100;
  int ciclo = map(volts, 0, 330, 0, 255);
  int ultimo_tempo = 0;
  while (ciclos > 0 ) {
    ciclos--;
    if (millis() - ultimo_tempo > tempo) {
      ultimo_tempo = millis();
      if (getSentido()) {

      }
    }
  }
}

void Motor::potControle(int tensao) {
  int freq = map(tensao, 0, 330, 0, 255);
  tensao -= 165;
  if (tensao > 0) {
    digitalWrite(getPino1(), 1);
    digitalWrite(getPino2(), 0);
    analogWrite(getVelocidade(), freq);
    setSentido(HORARIO); //Pino 1 ativado, sentido bool == 0
    //system.println("e");
  } else {
    if (tensao == 0) {
      stopMotor();
      setSentido(PARADO);
    } else {
      digitalWrite(getPino1(), 0);
      digitalWrite(getPino2(), 1);
      analogWrite(getVelocidade(), freq);
      setSentido(ANTI_HORARIO);
    }
  }
}

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}
