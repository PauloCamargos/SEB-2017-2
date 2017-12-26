#define PPOT  A0
#define PLDR  A1
#define PLAMP 11
#define PBUTTON 12
int lamp_pwm;
float val_min = 0.5; // Valor em %

void setup() {
  // put your setup code here, to run once:
  pinMode(PLAMP, OUTPUT);
  pinMode(PBUTTON, INPUT_PULLUP);
  Serial.begin(9600);
}

void loop() {
  lamp_pwm = map(analogRead(PLDR), 0, 1023, 255, 0);
  if (!digitalRead(PBUTTON)) {
    if ( analogRead(PPOT) <  val_min * 1023)
    {
      analogWrite(PLAMP, 255);
      Serial.println("MAXIMO - PWM: 255");
    } else {
      analogWrite(PLAMP, lamp_pwm);
      Serial.println("ACESO - PWM: " + (String) lamp_pwm);
    }
  } else
    analogWrite(PLAMP, 0);
}



