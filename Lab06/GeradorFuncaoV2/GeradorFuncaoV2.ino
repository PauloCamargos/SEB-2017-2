#define pin_bQ 11
#define pin_bT 10
#define pin_bS 9
#define pin_pot A0
//float rads, passo, seno[4095];
int voltage;
int freq; // Vai de 1 até 10 Hz
long periodo; //ms
float valsin;
int amplit;
void setup() {
  // put your setup code here, to run once:
  pinMode(pin_bQ, INPUT_PULLUP);
  pinMode(pin_bT, INPUT_PULLUP);
  pinMode(pin_bS, INPUT_PULLUP);
  //pinMode(DAC0, OUTPUT);
  Serial.begin(115200);
  //  analogWriteResolution(12);

  //  passo = (2.0 * PI) / 4095.0; // 360º / 4095
  //  for (int i = 0; i < 4095; i++) // vetor seno de 1 a -1
  //    seno[i] = (sin(i * passo) + 1);
}

void sinusoidal(int periodo, int amplitude) {
  for (int i = 0; i < 512; i++) {
    valsin = 1 + (sin((1 * i * 2 * PI) / 512));
    //analogWrite(DAC0, (amplitude * valsin));
    //    Serial.print(6000);
    //    Serial.print(" ");
    //    Serial.print(-1000);
    //    Serial.print(" ");
    Serial.println( valsin * amplitude / 2);
    //unsigned long _periodo = ( 1000 * periodo) / 512;
    delay(periodo / 512);
  }
}

void squared(int periodo, int amplitude) {
  for (int i = 0; i < 512; i++) {
    //analogWrite(DAC0, amplitude);
    Serial.println(amplitude);
    delay(periodo  / 512 * 2);
  }
  for (int i = 511; i >= 0; i--) {
    //analogWrite(DAC0, i);
    Serial.println(0);
    delay(periodo / 512 * 2);
  }
}

void triangular(int periodo) {
  long _periodo = (1000 * periodo ) / (256 * 2);
  for (int i = 0; i < 256; i++) {
    //analogWrite(DAC0, i);
    Serial.println(i * 16);
    delayMicroseconds(_periodo);
  }
  for (int i = 255; i >= 0; i--) {
    //analogWrite(DAC0, i);
    Serial.println(i * 16);
    delayMicroseconds(_periodo);
  }
}

void loop() {
  freq = map(analogRead(A0), 0, 1023, 1, 100);
  periodo = (1 / freq) * 1000; //em us201
  int amplit = 4096;
  //periodo = (2 * analogRead(pin_pot)) / 1023.0; //Comentar caso nao estiver usando o potenciometro.

  if (!digitalRead(pin_bS)) {
    sinusoidal(periodo, amplit);
  } else if (!digitalRead(pin_bQ)) {
    squared(periodo, amplit);
  } else if (!digitalRead(pin_bT)) {
    triangular(periodo);
  } else {
    //analogWrite(DAC0, 0);
    Serial.println(0);
  }
}


