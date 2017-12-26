#define SEQ 13
#define RODA_PARA 12
#define VPOT A0
#define LED1 11
#define LED2 10
#define LED3 9
#define LED4 6
int tempo;
int elapsedT = 0;
int t;
byte ativadoSEQ1 = 0;
byte ativadoSEQ2 = 0;
void setup() {
  // put your setup code here, to run once:

  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
  pinMode(SEQ, INPUT_PULLUP);
  pinMode(RODA_PARA, INPUT_PULLUP);
  Serial.begin(9600);
}

int calculaTempo() {
  int tempo = map(analogRead(VPOT), 0, 1023, 100, 1000);
  return tempo;
}

void loop() {
  // put your main code here, to run repeatedly:

  t = calculaTempo();
  if (!digitalRead(RODA_PARA)) {
    tempo = millis();
    if (!digitalRead(SEQ)) {
      Serial.println("Sequencia 1   Tempo: " + (String) t + "ms");
      if ((tempo - elapsedT) > t && ativadoSEQ1 == 0) {
        elapsedT = millis();
        analogWrite(LED2, 0);
        analogWrite(LED3, 0);
        analogWrite(LED1, 0.2 * 255);
        analogWrite(LED4, 0.2 * 255);
        ativadoSEQ1 = 1;
      }
      tempo = millis();
      if ((tempo - elapsedT) > t && ativadoSEQ1 == 1) {
        elapsedT = millis();
        analogWrite(LED2, 0.8 * 255);
        analogWrite(LED3, 0.8 * 255);
        analogWrite(LED1, 0);
        analogWrite(LED4, 0);
        ativadoSEQ1 = 0;
      }
    } else {
      Serial.println("Sequencia 2   Tempo: " + (String) t + "ms");
      tempo = millis();
      if ((tempo - elapsedT) > t && ativadoSEQ2 == 0) {
        elapsedT = tempo;
        analogWrite(LED2, 0);
        analogWrite(LED3, 0);
        analogWrite(LED1, 0);
        analogWrite(LED4, 0);
        ativadoSEQ2 = 1;
      }
      tempo = millis();
      if ((tempo - elapsedT) > t && ativadoSEQ2 == 1) {
        elapsedT = millis();
        analogWrite(LED2, 0);
        analogWrite(LED3, 0);
        analogWrite(LED1, 0.2 * 255);
        analogWrite(LED4, 0);
        ativadoSEQ2 = 2;
      }
      tempo = millis();
      if ((tempo - elapsedT) > t && ativadoSEQ2 == 2) {
      elapsedT = millis();
        analogWrite(LED2, 0.4 * 255);
        analogWrite(LED3, 0);
        analogWrite(LED1, 0.4 * 255);
        analogWrite(LED4, 0);
        ativadoSEQ2 = 3;
      }
      tempo = millis();
      if ((tempo - elapsedT) > t && ativadoSEQ2 == 3) {
      elapsedT = millis();
        analogWrite(LED2, 0.7 * 255);
        analogWrite(LED3, 0.7 * 255);
        analogWrite(LED1, 0.7 * 255);
        analogWrite(LED4, 0);
        ativadoSEQ2 = 4;
      }
      tempo = millis();
      if ((tempo - elapsedT) > t && ativadoSEQ2 ==4) {
        elapsedT = millis();
        analogWrite(LED2, 255);
        analogWrite(LED3, 255);
        analogWrite(LED1, 255);
        analogWrite(LED4, 255);
        ativadoSEQ2 = 0;
      }
    }
  } else {
    
    analogWrite(LED1, 0);
    analogWrite(LED2, 0);
    analogWrite(LED3, 0);
    analogWrite(LED4, 0);
    Serial.println("-------- SEQUENCIA INTERROMPIDA -------");
  }
}
