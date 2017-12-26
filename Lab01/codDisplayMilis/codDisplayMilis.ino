// Definição das variáveis para controle do intervalo de tempo
unsigned long tempo_controle = 0; // Recebe o último tempo registrado
unsigned long intervalo = 300; // Intervalo de tempo para mudança do número no display
byte numero;
/* Array para definição dos LEDs que serão ligados para cada número
// As linhas representam o número a ser exibido. As colunas 
apresentam o estado (1 ou 0) de cada segmento:(A,B,C,D,E,F,G) */ 
byte display_7seg[10][7] = {  { 0, 0, 0, 0, 0, 0, 1 }, // = Digito 0
  { 1, 0, 0, 1, 1, 1, 1 }, // = Digito 1
  { 0, 0, 1, 0, 0, 1, 0 }, // = Digito 2
  { 0, 0, 0, 0, 1, 1, 0 }, // = Digito 3
  { 1, 0, 0, 1, 1, 0, 0 }, // = Digito 4
  { 0, 1, 0, 0, 1, 0, 0 }, // = Digito 5
  { 0, 1, 0, 0, 0, 0, 0 }, // = Digito 6
  { 0, 0, 0, 1, 1, 1, 1 }, // = Digito 7
  { 0, 0, 0, 0, 0, 0, 0 }, // = Digito 8
  { 0, 0, 0, 1, 1, 0, 0 }, // = Digito 9
};

//Definição do tipo de trabalho de cada pino conectado ao display
void setup() {
  pinMode(2, OUTPUT); // seg A, pino 2 arduino, 7 (no display)
  pinMode(3, OUTPUT); // seg B, pino 3 arduino, 6 (no display)
  pinMode(4, OUTPUT); // seg C, pino 4 arduino, 4 (no display)
  pinMode(5, OUTPUT); // seg D, pino 5 arduino, 2 (no display)
  pinMode(6, OUTPUT); // seg E, pino 6 arduino, 1 (no display)
  pinMode(7, OUTPUT); // seg F, pino 7 arduino, 9 (no display)
  pinMode(8, OUTPUT); // seg G, pino 8 arduino, 10 (no display)
  pinMode(9, OUTPUT); // ponto, pino 9 arduino, 5 (no display)
}

// Função para exibição do número no display
void exibeNumero(byte numero) {
  byte pino_atual = 2;
  for (byte i = 0; i < 7; ++i) {
    digitalWrite(pino_atual, display_7seg[numero][i]);
    ++pino_atual;
  }
}

void loop() { 
  numero = 0; // Armazena o número para ser exibido de 0 a  9
  for (numero; numero <10;) {
    unsigned long tempo_atual = millis(); // Armazena o tempo atual
    if ((tempo_atual - tempo_controle) >= intervalo) { //Faz a verificação se o intervalo foi 'estourado'
      tempo_controle = tempo_atual;                    //Armazena o valor útlimo do intervalo estourado
      exibeNumero(numero);          // Chama a função para exibir o número no display
      ++numero;                     // Incrementa o número
    }
  }
}

