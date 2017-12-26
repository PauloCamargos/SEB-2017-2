#define pinAnalog A1
int leitura;
int int_tensao;
float tensao;
float tens;
void setup() {
  Serial.begin(9600);

}
void loop() {
  analogReadResolution(10); 
  leitura = analogRead(pinAnalog);
  Serial.println(leitura);
  int_tensao = map(leitura, 0, 675, 0, 33);
  tensao = int_tensao / 10;
  Serial.print("MAP: ");
  Serial.println(tensao);

  tens = leitura * (3.3/675);
  Serial.print("CALC: ");
  Serial.println(tens);
  delay(1000);
}

