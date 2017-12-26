/* Programa para controle da tensao em um sistema RC (capacitor)
   utilizando controlador P.
   Passo a passo:
   1) Config Kp
   2) Ler Vcapacitor
   3) Calcular erro
   4) Injetar tensao e(t) * Kp
   5) Repete a partir de 3
*/

//https://www.embarcados.com.br/controlador-proporcional-eletronico/

#define LED_PIN      13      // Led controlador P
#define START_PIN    12      // Botao inicio
#define PWM_PIN      11      // Pin saida sinal SP em PWM
#define ANALOG_PIN   DAC0    // Pin conectado ao DAC1;
#define REF_PIN      A0      // Pin conectado ao potenciometro
#define PV_PIN       A1      // Pin Vcapacitor do capacitor

float Kp = 0, erro = 0, Vcapacitor = 0, Vreferencia = 0, SA = 0; //SA = Sinal atuante
float sinalAtuante = 0;
// SA é o sinal de correcao.
void setup() {
  pinMode(LED_PIN, OUTPUT);
  pinMode(START_PIN, INPUT_PULLUP);
  pinMode(PWM_PIN, OUTPUT);
  Serial.begin(115200);
  analogReadResolution(12);
  analogWriteResolution(12);
}

//void aplicaSinal(float sinalAtuante) {
//  int periodo = 100; // em ms
//  for (int i = 0; i < 512; i++) {
//    analogWrite(ANALOG_PIN, (sinalAtuante * 4095.0) / Vi);
//    Serial.println((sinalAtuante * 4095.0) / Vi);
//    delayMicroseconds((periodo / 512) * 1000 );     // 100ms/512pt convertido para us.
//  }
//}

void loop() {
  if (!digitalRead(START_PIN)) {
    digitalWrite(LED_PIN, 1);
    Vcapacitor = 3.3 * analogRead(PV_PIN) / 4095.0;       // Ler tensao Vcapacitor
    Vreferencia = 3.3 * analogRead(REF_PIN) / 4095.0;    // Ler tensao referencia
    erro = Vreferencia - Vcapacitor;                     // Calculo do erro

    //aplicaSinal(SA);                                  //Chave na posicao Analog (DAC0)
    if (erro >= 0) {
      sinalAtuante = erro * Kp;
      if(sinalAtuante > 4095)
        sinalAtuante  = 4095;
    } else {
      SA = 0;
    }
    analogWrite(ANALOG_PIN, sinalAtuante);
    analogWrite(PWM_PIN, (SA * 255) / Vreferencia);           //Chave na posicao PWM
  }
}
