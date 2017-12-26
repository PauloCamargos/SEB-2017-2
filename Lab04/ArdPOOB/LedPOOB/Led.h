class Led {
  private:
    int _porta;
    bool _estado;
  public:
    Led(int porta);
    int getPorta();
    bool getEstado();
    void Pisca(int tempo, int vezes);
    void Apaga();
    void Acende();
    void ligaPWM(int vezes);
};

Led::Led(int porta) {
  this->_porta = porta ;
}
int Led::getPorta() {
  return this->_porta;
}

bool Led::getEstado() {
  return digitalRead(this->getPorta());
}


void Led::Pisca(int tempo, int vezes) {
  while (vezes > 0) {
    digitalWrite(getPorta(), 1);
    delay(tempo);
    digitalWrite(getPorta(), 0);
    delay(tempo);
    vezes--;
  }
}

void Led::Apaga() {
  digitalWrite(getPorta(), 0);
}
void Led::Acende() {
  digitalWrite(getPorta(), 1);
}

void Led::ligaPWM(int vezes) {
  while (vezes > 0) {
    for (int i = 0; i <=256; i += 5) {
      analogWrite(this->getPorta(), i);
      delay(30);
    }
    for (int i = 255; i >= 0; i -= 5) {
      analogWrite(this->getPorta(), i);
      delay(30);
    }
    vezes--;
  }
}
