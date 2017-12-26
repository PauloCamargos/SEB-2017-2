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
//https://www.youtube.com/watch?v=txftR4TqKYA

#define LED_PIN      13      // Led controlador P
#define START_PIN    12      // Botao inicio
#define PWM_PIN      11      // Pin saida sinal SP em PWM
#define ANALOG_PIN   DAC0    // Pin conectado ao DAC1;
#define REF_PIN      A0      // Pin conectado ao potenciometro
#define PV_PIN       A1      // Pin Vcapacitor do capacitor

int sinalAbits = 0;
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

void loop() {
  if (!digitalRead(START_PIN)) {
    digitalWrite(LED_PIN, 1);
    Vcapacitor = 3.3 * analogRead(PV_PIN) / 4095.0;       // Ler tensao Vcapacitor
    Vreferencia = 3.3 * analogRead(REF_PIN) / 4095.0;    // Ler tensao referencia
    erro = Vreferencia - Vcapacitor;                     // Calculo do erro
    sinalAtuante = erro * Kp;   // Calculo do sinal atuante.

    if (erro >= 0) { // Caso erro seja positivo
      sinalAbits = map(sinalAtuante, 0, Kp * 3.3, 0, 4095); //Converte sinal atuante para Binario
      if (sinalAtuante > 3.3)  // Configura o limite maximo do sinal autante
        sinalAbits = 4095;
    } else {    // Caso o erro seja negativo
      sinalAbits = map(sinalAtuante, 0, Kp * 3.3, 4095, 0);  // Convete sinal atuante para Binario
      if (sinalAtuante < 0)     // Caso seja negativo, configura o limite minimo.
        sinalAbits = 0;
    }
    analogWrite(ANALOG_PIN, sinalAbits);         // Chave na posicao Analog
    analogWrite(PWM_PIN, sinalAbits);           //Chave na posicao PWM
  }
}
