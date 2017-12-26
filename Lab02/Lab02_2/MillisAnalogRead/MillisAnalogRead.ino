//definição dos pinos
#define pinAnalogico    A0
#define pinButton       13
#define ledVM_D3        10
#define ledVD_D2        9
#define ledVM_D1        8
const int intervalo = 700; int elapsed_time = 0; int last_time = 0; // Variáveis de controle da função millis()

void setup() {
  pinMode(pinButton, INPUT_PULLUP);
  pinMode(ledVM_D3, OUTPUT);
  pinMode(ledVD_D2, OUTPUT);
  pinMode(ledVM_D1, OUTPUT);
  Serial.begin(57600);
}

void loop() {
  elapsed_time = millis();
  if ((elapsed_time - last_time) > intervalo) {
    last_time = elapsed_time;
    int valorSensor = analogRead(pinAnalogico);
    //float tensao = valorSensor * (5.0 / 1023.0);

    //int  tensao_int = map(valorSensor,0,1023,0,500); // UNO
    int  tensao_int = map(valorSensor, 0, 1023, 0, 330); // due
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
  }
}
