#define pinSensor         A1
#define pinReferencia     A0
#define pinStart          8
#define pinKp             A2
void setup() {
  // put your setup code here, to run once:
  pinMode(pinStart, INPUT_PULLUP);
  Serial.begin(115200);
  analogReadResolution(12);
  analogWriteResolution(12);
}
float getKP(){
  // 0 < Kp < 100 
  return analogRead(pinKp) * 100 / 4095.0;
}
void loop() {
  // put your main code here, to run repeatedly:
  if(!digitalRead(pinStart)){
    // Vout:  0 - 3.3
    //        0 - 4095
    float Vout = analogRead(pinSensor);
    // 0    -> Vout > Vreferencia
    // 4095 -> Vout = Vreferencia
    // 8190 -> Vout < Vreferencia
    float erro = analogRead(pinReferencia) - Vout  + 4095;
    float mp = erro * getKP();
    
  }
}
