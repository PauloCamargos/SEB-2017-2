#define pin_bQ 13
#define pin_bT 12
#define pin_bS 11
#define pin_pot A0
float rads, passo, seno[4095];
int voltage;
long periodo = 100;

void setup() {
  // put your setup code here, to run once:
  pinMode(pin_bQ, INPUT_PULLUP);
  pinMode(pin_bT, INPUT_PULLUP);
  pinMode(pin_bS, INPUT_PULLUP);
  pinMode(DAC0, OUTPUT);
  Serial.begin(9600);
  analogWriteResolution(12);

  passo = (2.0 * PI) / 4095.0; // 360º / 4095
  for (int i = 0; i < 4095; i++) // vetor seno de 1 a -1
    seno[i] = (sin(i * passo) + 1);
}

void sinusoidal(int periodo, int amplitude) {
  for (int i = 0; i < 4096; i++) {
    analogWrite(DAC0, (amplitude * seno[i]));
    delay(periodo / 4096);
  }
}

void squared(int periodo, int amplitude) {
  analogWrite(DAC0, amplitude);
  delay(periodo / 2.0);
  analogWrite(DAC0, 0);
  delay(periodo / 2.0);
}

void triangular(int periodo, int amplitude) {
  for (int i = 0; i < 4096; i++) {
    analogWrite(DAC0, i);
    delay(periodo / (4096.0 * 2.0));
  }
  for (int i = 4096; i >= 0; i--) {
    analogWrite(DAC0, i);
    delay(periodo / (4096.0 * 2.0));
  }
}

void loop() {
  int amplit = 3.3;
  //periodo = (2 * analogRead(pin_pot)) / 1023.0; //Comentar caso nao estiver usando o potenciometro.

  if (!digitalRead(pin_bS)) {
    sinusoidal(periodo, amplit);
  } else {
    if (!digitalRead(pin_bQ)) {
      squared(periodo, amplit);
    } else {
      if (!digitalRead(pin_bT)) {
        triangular(periodo, amplit);
      } else {
        analogWrite(DAC0, 0);
      }
    }
  }
}
