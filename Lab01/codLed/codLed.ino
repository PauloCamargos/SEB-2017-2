// Definição dos pinos
#define ledVermelho 13
#define ledAmarelo 12
#define ledVerde 11
#define pinButton 10

void setup() {
  // Definição do tipo de trabalho do pino: input ou output
  pinMode(ledVermelho, OUTPUT);
  pinMode(ledAmarelo, OUTPUT);
  pinMode(ledVerde, OUTPUT);
  pinMode(pinButton, INPUT_PULLUP);
}

void loop() {
  // Código para rotina de acendimento do semáforo
  if (digitalRead(pinButton)) {   // Executa caso o botão não esteja pressionado 
    digitalWrite(ledVermelho, 1); // Acende o ledVermelho
    delay(3000);                  // "Segura" o programa durante 3 segundos
    digitalWrite(ledVermelho, 0); // Desliga o ledVermelho
    
    digitalWrite(ledVerde, 1);
    delay(2000);
    digitalWrite(ledVerde, 0);

    digitalWrite(ledAmarelo, 1);
    delay(1000);
    digitalWrite(ledAmarelo, 0);
  } else { // Executa caso o botão esteja pressionado 
    digitalWrite(ledVermelho, 0); //Desliga o ledVermelho
    digitalWrite(ledVerde, 0);    // Desliga o ledVerde
    // Pisca o ledAmarelo por 0.5s 
    digitalWrite(ledAmarelo, 1);  
    delay(500); 
    digitalWrite(ledAmarelo, 0);
    delay(500);
  }
}
