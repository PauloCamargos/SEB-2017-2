//Definição dos pinos
#define pinAnalogico    A0
#define pinButton       12
#define ledVM_D3        10
#define ledVD_D2        9
#define ledVM_D1        8

void setup() {
  //Configuração do regime de trabalho dos pinos e comunicação serial
  pinMode(pinButton, INPUT_PULLUP);
  pinMode(ledVM_D3, OUTPUT);
  pinMode(ledVD_D2, OUTPUT);
  pinMode(ledVM_D1, OUTPUT);
  Serial.begin(115200); // Inicia porta serial
}

void loop() {
  //Realiza a leitura retornando valores de unidade entre 0-1023 (0-3.3V)
  int valorSensor = analogRead(pinAnalogico);
  //Realiza conversão
  int  tensao_int = map(valorSensor, 0, 1023, 0, 330); // SOMENTE PARA DUE
  float tensao = tensao_int / 100.0;

  Serial.print("A tensao analogica apresentada na entrada A0 do ARDUINO e igual a: ");
  Serial.println(tensao);
  if (!digitalRead(pinButton)) {
    if (tensao < 1.0) {
      digitalWrite(ledVM_D1, 1);
      digitalWrite(ledVD_D2, 0);
      digitalWrite(ledVM_D3, 0);
    } else {
      if (tensao < 2) {
        digitalWrite(ledVD_D2, 1);
        digitalWrite(ledVM_D1, 0);
        digitalWrite(ledVM_D3, 0);
      } else {
        digitalWrite(ledVM_D3, 1);
        digitalWrite(ledVM_D1, 0);
        digitalWrite(ledVD_D2, 0);
      }
    }
  } else {
    digitalWrite(ledVM_D1, 0);
    digitalWrite(ledVD_D2, 0);
    digitalWrite(ledVM_D3, 0);
  }
  delay(300);
}
