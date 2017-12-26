/* Implementation of a P controler for a RC circuit.
Authors:  Paulo Camargos Siva
          Nathalia Rodrigues
          Italos G. S. Fernandes
*/

#define pinSensor         A9 // Vout pin
#define pinReferencia     A8
#define pinStart          8
#define pinKp             A2
#define pinPWM            11

void setup() {
  pinMode(pinStart, INPUT_PULLUP);
  pinMode(pinPWM, OUTPUT);
  Serial.begin(115200);
  analogReadResolution(12);
  analogWriteResolution(12);
}

void loop() {
  if (!digitalRead(pinStart)) {
    int Vout = analogRead(pinSensor);   // Reading capacitor voltage
    int ref = analogRead(pinReferencia);  // Reading reference voltage
    int erro = ref - Vout;                
    int Kp = analogRead(pinKp) * 20 / 4095.0; // 0 < Kp < 20. Ajustable as potenciometer
    int P = erro * Kp;

    // Returns
    // # P, if 0 < P < 4095;
    // # 0, if P<0;
    // # 4095, if P>4095. 
    P = constrain(P, 0, 4095); 
    analogWrite(DAC1, P);
    Serial.println("Kp: " + (String) Kp + 
      "| P: " + (String) P + "| Ref: " + (String) ref + "| Vout: " + (String) Vout);
    analogWrite(pinPWM, P);
  }
}

