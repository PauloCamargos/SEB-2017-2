#define pinENB 10
#define pinIn4 9
#define pinIn3 8
#define pinPot A0
#define pinFR 12
// #define pinLD 13
const int buttonPin = 2;    // the number of the pushbutton pin
const int ledPin = 13;      // the number of the LED pin

// Variables will change:
int estadosistema = HIGH;         // the current state of the output pin
int buttonState;             // the current reading from the input pin
int lastButtonState = LOW;   // the previous reading from the input pin

// the following variables are unsigned longs because the time, measured in
// milliseconds, will quickly become a bigger number than can be stored in an int.
unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 50;

void setup() {
  pinMode(pinENB, OUTPUT);
  pinMode(pinIn4, OUTPUT);
  pinMode(pinIn3, OUTPUT);
  pinMode(pinPot, INPUT);
  pinMode(pinFR, INPUT_PULLUP);
  // pinMode(pinLD, INPUT_PULLUP);
  pinMode(buttonPin, INPUT_PULLUP); // liga e desliga motor
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

float calctensao() {
  int leitura = analogRead(pinPot); // valor de tensao vai de 0 a 1023, vou usar funcao map para tranformar de 0 a 3.3.
  float tensao = leitura * 3.3 / 1023; //map(tensaoPot, 0, 1023, 0, 330) / 100.0; // map(variavel a ser convertida, minimo da variavel a ser convertida, maximo da variavel a ser conv, minimo do valor convertido, maximo do valor conv)
  // usa-se 330 pq e float, depois divide por 3.3 para dar o int
  return tensao;
}

void loop() {

  // read the state of the switch into a local variable:
  int reading = digitalRead(buttonPin);

  // check to see if you just pressed the button
  // (i.e. the input went from LOW to HIGH), and you've waited long enough
  // since the last press to ignore any noise:

  // If the switch changed, due to noise or pressing:
  if (reading != lastButtonState) { // verifica se estado esta diferente do anterior
    // reset the debouncing timer
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    // whatever the reading is at, it's been there for longer than the debounce
    // delay, so take it as the actual current state:

    // if the button state has changed:
    if (reading != buttonState) {
      buttonState = reading;

      // only toggle the LED if the new button state is HIGH
      if (buttonState == HIGH) {
        estadosistema = !estadosistema;
      }
    }
  }


  // save the reading. Next time through the loop, it'll be the lastButtonState:
  lastButtonState = reading;
  if (estadosistema == HIGH) {
    if (pinFR == HIGH) {
      analogWrite(pinENB, 255);
      digitalWrite(pinIn4, HIGH);
      digitalWrite(pinIn3,  HIGH);
    } else {
      if (calctensao() == 3.3 / 2) {
        analogWrite(pinENB, LOW);
        digitalWrite(pinIn4, LOW);
        digitalWrite(pinIn3,  LOW);
      }
      else if (calctensao() > 3.3 / 2) {
        int velocidade = (calctensao() - 1.65) * 255 / 1.65;
        analogWrite(pinENB, velocidade);
        digitalWrite(pinIn4, 1);
        digitalWrite(pinIn3,  LOW);
      }
      else if (calctensao() < 3.3 / 2) {
        int velocidade = (calctensao() - 1.65) * 255 / -1.65;
        analogWrite(pinENB, velocidade);
        digitalWrite(pinIn4,  LOW);
        digitalWrite(pinIn3, 1);
      }
    }

  }
}
