#define pinSaida 11
#define pinButton 12
#define pinPot A0

int tensaoPot = 0;

void setup() {
  pinMode(pinSaida, OUTPUT);
  pinMode(pinButton, INPUT_PULLUP); // ativa resistor interno PULLUP
  Serial.begin(9600);
  Serial.print("Arduino Ligado.");
}

void loop() {
  tensaoPot =  analogRead(pinPot); // le pino de entrada, analogRead retorna valores de 0 a 1023
  if (digitalRead(pinButton) == HIGH) {
    analogWrite(pinSaida, tensaoPot / 4); // analogWrite vai de 0 a 255, entao fazendo regra de 3 tem q dividir por 4
  } else {
    analogWrite(pinSaida,0); // se chave estiver apertada fica em LOW = 0, pinSaida = 0.
  }
  Serial.print("Tensao em A0 = ");
  Serial.print(tensaoPot*3.3/1023,1); // 1023 equivale a 3.3, tensaoPot equivale a x, regra de tres para converter em tensao, com 1 casa decimal
  Serial.print(" volts Sinal PWM = ");
  Serial.print((tensaoPot/4)*100/255); // quantos % de 255 que vale tensaoPot/4
  Serial.println("%");
}
