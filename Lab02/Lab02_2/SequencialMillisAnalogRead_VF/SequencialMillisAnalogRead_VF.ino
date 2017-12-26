//definição dos pinos
#define pinAnalogico    A0
#define ledVM_D3        10
#define ledVD_D2        9
#define ledVM_D1        8
int ledAtual = 10; // Pino do LED que está ON
// Variáveis de controle da função millis()
const int intervalo =   200;
int tempo_atual =       0;
int ultimo_tempo =      0;

void setup() {
  //Configuração do regime de trabalho dos pinos e comunicação serial
  pinMode(ledVM_D3, OUTPUT);
  pinMode(ledVD_D2, OUTPUT);
  pinMode(ledVM_D1, OUTPUT);
  Serial.begin(57600); // Inicia porta serial
}

void exibeTensao(float tensao, int intervalo) {
  //Função para exibição da tensão no monitor serial
  Serial.print("A tensao analogica apresentada na entrada A0 do ARDUINO e igual a: ");
  Serial.println(tensao);
  Serial.print("Intervalo: ");
  Serial.println(intervalo * tensao);
}

float lerTensao() {
  //Função para leitura e conversão dos valores de tensão
  int valorSensor = analogRead(pinAnalogico);
  int  tensao_int = map(valorSensor, 0, 1023, 0, 330);
  float tensao = tensao_int / 100.0;
  return tensao;
}

void ligaLED() {
  //Função para ativação sequencial dos LED's
  switch (ledAtual) { //Verifica qual LED está ligado no momento
    case (10): {
        // Liga LED do pin 9 (ledVD_D2)
        digitalWrite(ledVM_D1, 0);
        digitalWrite(ledVD_D2, 1);
        digitalWrite(ledVM_D3, 0);
        ledAtual = 9;
        break;
      }
    case (9): {
        // Liga LED do pin 8 (ledVM_D1)
        digitalWrite(ledVM_D1, 1);
        digitalWrite(ledVD_D2, 0);
        digitalWrite(ledVM_D3, 0);
        ledAtual = 8;
        break;
      }
    case (8): {
        // Liga LED do pin 10 (ledVM_D3)
        digitalWrite(ledVM_D1, 0);
        digitalWrite(ledVD_D2, 0);
        digitalWrite(ledVM_D3, 1);
        ledAtual = 10;
        break;
      }
    default: {
        // Desliga todos LED's
        digitalWrite(ledVM_D1, 0);
        digitalWrite(ledVD_D2, 0);
        digitalWrite(ledVM_D3, 0);
        ledAtual = 10;
      }
  }
}

void loop() {
  tempo_atual = millis();       // Tempo desde o inicio do funcionamento (ms)
  float tensao = lerTensao();   // Armazena valor de tensão lido na porta analog.
  // Verifica se o tempo de intervalo estourou
  if ((tempo_atual - ultimo_tempo) > (intervalo * tensao)) {
    ultimo_tempo = tempo_atual;
    exibeTensao(tensao, intervalo); // Exibe mensagem no serial monitor
    ligaLED();                      // Liga o LED
  }
}
