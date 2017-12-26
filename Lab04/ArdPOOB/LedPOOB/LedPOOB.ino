#include "Led.h"

Led *led1;
Led *led2;

void setup() {
  // put your setup code here, to run once:
  led1 = new Led(6);
  led2 = new Led(5);
  pinMode(led1->getPorta(), OUTPUT);
  pinMode(led2->getPorta(), OUTPUT);  
  Serial.begin(9600);
  Serial.println("------------- PROGRAMA INICIADO ---------------");
  Serial.println("LED 1 - Porta: " + (String) led1->getPorta());
  Serial.println("LED 2 - Porta: " + (String) led2->getPorta());

}

void loop() {
  // put your main code here, to run repeatedly:
  led1->Acende();
  led2->Acende();
  delay(2000);
  led1->Apaga();
  led2->Apaga();
  delay(2000);

  led1->Pisca(100, 5);
  led2->Pisca(200, 5);

  led1->ligaPWM(4);
  led2->ligaPWM(4);
}
