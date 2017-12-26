//Definição dos pinos
#define pinAnalogico    A0
#define pinButton       13
#define pinMotor        6 // PWM

void setup() {
  //Configuração do regime de trabalho dos pinos e comunicação serial
  pinMode(pinButton, INPUT_PULLUP);
  pinMode(pinMotor, OUTPUT);
  Serial.begin(115200); // Inicia porta serial
}

float lerTensao() { 
  //Realiza a leitura retornando valores de unidade entre 0-1023 (0-3.3V)
  int valorSensor = analogRead(pinAnalogico);
  //Realiza conversão
  //  int  tensao_int = map(valorSensor, 0, 1023, 0, 330); // SOMENTE PARA DUE
  int  tensao_int = map(valorSensor, 0, 1023, 0, 500); // SOMENTE PARA UNO
  float tensao = tensao_int;
  return tensao;
}

void exibeMensagem(float tensao, int rc) {
  float rc_perc = rc * 100.0 / 255;
  Serial.println("A tensao em AO =  " + (String)tensao + " volts  Sinal PWM = " + (String)rc_perc + "%" + " Value RC = " + (String)rc);
  //Serial.print("A tensao em AO =  ")
  //Serial.println(tensao) + " volts  Sinal PWM = " + String(rc_perc) + "%");
}

int calculaRC(float tensao) {
  int rc = map(tensao, 0, 500, 0, 255);
  return rc;
}
void loop() {
  float tensao = lerTensao();
  int rc = calculaRC(tensao);
  tensao /= 100.0;
  exibeMensagem(tensao, rc);
  if (!digitalRead(pinButton)) {
    analogWrite(pinMotor, rc);
  } else {
    analogWrite(pinMotor, 0);
  }
}
