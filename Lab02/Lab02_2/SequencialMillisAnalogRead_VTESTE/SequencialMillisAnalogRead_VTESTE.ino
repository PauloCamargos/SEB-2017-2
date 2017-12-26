//definição dos pinos
#define pinAnalogico    A0
#define pinButton       12
//#define ledVM_D3        10
//#define ledVD_D2        9
//#define ledVM_D1        8
int ledAtual =          10;
const int intervalo =   100;
int tempo_atual =       0;
int ultimo_tempo =      0; // Variáveis de controle da função millis()
byte mat_leds[5][3] = { {1, 0, 0},
  {0, 1, 0},
  {0, 0, 1},
  {1, 1, 1},
  {0, 0, 0}
};

void setup() {
  pinMode(pinButton, INPUT_PULLUP);
  //pinMode(ledVM_D3, OUTPUT);
  //pinMode(ledVD_D2, OUTPUT);
  //pinMode(ledVM_D1, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(8, OUTPUT);
  Serial.begin(57600);
}

void exibeTensao(float tensao, int intervalo) {
  Serial.print("A tensao analogica apresentada na entrada A0 do ARDUINO e igual a: ");
  Serial.println(tensao);
  Serial.print("Intervalo: ");
  Serial.println(intervalo * tensao);
}

float lerTensao() {
  int valorSensor = analogRead(pinAnalogico);
  //int  tensao_int = map(valorSensor,0,1023,0,500); // UNO
  int  tensao_int = map(valorSensor, 0, 739, 0, 330); //DUE
  float tensao = tensao_int / 100.0;
  return tensao;
}

void acendeLeds() {
  for (int i = 0; i < 3; i++) {
    int pino = 8;
    for (int j = 0; j < 3; j++) {
      digitalWrite(pino, mat_leds[i][j]);
//      Serial.println("Pino: ");
//      Serial.print(pino);
      ++pino;
//      delay(1000);
    }
  }
}


//void ligaLED() {
//  switch (ledAtual) {
//    case (10): {
//        digitalWrite(ledVM_D1, 0);
//        digitalWrite(ledVD_D2, 1);
//        digitalWrite(ledVM_D3, 0);
//        ledAtual = 9;
//        break;
//      }
//    case (9): {
//        digitalWrite(ledVM_D1, 1);
//        digitalWrite(ledVD_D2, 0);
//        digitalWrite(ledVM_D3, 0);
//        ledAtual = 8;
//        break;
//      }
//    case (8): {
//        digitalWrite(ledVM_D1, 0);
//        digitalWrite(ledVD_D2, 0);
//        digitalWrite(ledVM_D3, 1);
//        ledAtual = 10;
//        break;
//      }
//    default: {
//        digitalWrite(ledVM_D1, 0);
//        digitalWrite(ledVD_D2, 0);
//        digitalWrite(ledVM_D3, 0);
//        ledAtual = 10;
//      }
//  }
//}

void loop() {
  if (!digitalRead(pinButton)) {
    Serial.println("Botao pressionado!!");
    //    digitalWrite(ledVM_D1, 1);
    //    digitalWrite(ledVD_D2, 1);
    //    digitalWrite(ledVM_D3, 1);
  } else {
    tempo_atual = millis();
    float tensao = lerTensao();
    if ((tempo_atual - ultimo_tempo) > (intervalo * tensao)) {
      ultimo_tempo = tempo_atual;
      exibeTensao(tensao, intervalo);
      //ligaLED();
      acendeLeds();
    }
  }
}
