#define pinQ 6
#define pinT 8
#define pinS 4
//#define pinPot A0
//#define pinOsc DAC0

int y;
int i;
int j;
int k;
long period;
void setup() {
  //analogWriteResolution(12);
  pinMode(pinQ, INPUT_PULLUP);
  pinMode(pinT, INPUT_PULLUP);
  pinMode(pinS, INPUT_PULLUP);
  //  pinMode(pinPot, INPUT_PULLUP);
  //pinMode(pinOsc, OUTPUT);
  delay(100);
  Serial.begin(9600);
}

void loop() {
  if (digitalRead(pinQ) == LOW) {
    //analogWrite(pinOsc, LOW);
    Serial.println(0);
    delay(100);
    //analogWrite(pinOsc, 4095);
    Serial.println(4095);
    delay(100);
    Serial.println(4095);
    delay(100);
    //analogWrite(pinOsc, 4095);
    Serial.println(0);
    delay(100);
  }
  if (digitalRead(pinT) == LOW) {
    for (i = 0; i < 4096; i++) {
      //analogWrite(pinOsc, i);
      Serial.println(i);
      //delayMicroseconds(100);
      delay(100);
    }
    for (i = 4095; i >= 0; i--) {
      //analogWrite(pinOsc, j);
      Serial.println(i);
      //delayMicroseconds(12);
      delay(100);
    }
  }
  if (digitalRead(pinS) == LOW) {
    for (k = 0; k <= 360; k++) {
      y = (sin(k) + 1) * (4095 / 2);
      //analogWrite(pinOsc, y);
      Serial.println(y);
      //delayMicroseconds(277);
      delay(100);
    }
  }
}
