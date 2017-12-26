#define pinSensor         A9
#define pinReferencia     A8
#define pinStart          8
#define pinKp             A2
#define pinPWM            11

void setup() {
  // put your setup code here, to run once:
  pinMode(pinStart, INPUT_PULLUP);
  pinMode(pinPWM, OUTPUT);
  Serial.begin(115200);
  analogReadResolution(12);
  analogWriteResolution(12);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (!digitalRead(pinStart)) {
    // Vout:  0 - 3.3
    //        0 - 4095
    float Vout = analogRead(pinSensor);
    float ref = analogRead(pinReferencia);
    float erro = ref - Vout;
    float Kp = analogRead(pinKp) * 10 / 4095.0;
    float P = erro * Kp;

    P = constrain(P, 0, 4095); // P, se 0 < P < 4095, P<0 ->0, P>4095->4095
    analogWrite(DAC0, P);
    Serial.println("Kp: " + (String) Kp + "| P: " + (String) P + "| Ref: " + (String) ref + "| Vout: " + (String) Vout);
    //P = map(P, 0, Kp * 4095, 0, 255);
    //P = constrain(P, 0, 255);
    //println("Kp: " + (String) Kp + "| P: " (String) P);
    analogWrite(pinPWM, P);
  }
}

//float getKP() {
//  // 0 < Kp < 100
//  return  analogRead(pinKp) * 100 / 4095.0;
//}
