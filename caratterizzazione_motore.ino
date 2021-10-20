// CONFIGURAZIONE PIN
#define PIN_EN    0
#define PIN_IN1   1
#define PIN_IN2   2
#define PIN_PWM   3
#define PIN_ENC_A 4
#define PIN_ENC_B 5

unsigned long tempo;
int countRPM;

void setup() {
  // SERIALE
  Serial.begin(115200);
  Serial.println("Format: (time in milliseconds,direction of the step)");


  // DRIVER MOTORI
  //enable pin
  pinMode(PIN_EN, OUTPUT);

  //motore1
  pinMode(PIN_IN1, OUTPUT);
  pinMode(PIN_IN2, OUTPUT);
  pinMode(PIN_PWM, OUTPUT);
 
  digitalWrite(PIN_EN, HIGH);     //attivo il driver - enable
  analogWrite(PIN_PWM, 0);        // motore fermo

  // ENCODER
  pinMode(PIN_ENC_A,INPUT);
  pinMode(PIN_ENC_B,INPUT);
  attachInterrupt(digitalPinToInterrupt(PIN_ENC_A), handleEncoder, RISING);

  
  int tempo;
  for(int i = 0; i < 2; i++) {
    // avanti
    pinMode(PIN_IN1,HIGH);
    pinMode(PIN_IN2,LOW);

    // aspetto un secondo
    tempo = millis();
    while(millis() < tempo + 1000);

    // indietro
    pinMode(PIN_IN1,LOW);
    pinMode(PIN_IN2,HIGH);

    // aspetto un secondo
    tempo = millis();
    while(millis() < tempo + 1000);

  }

}

void loop(){}

//ISR dell'interrupt motore R, viene richiamata ad ogni fronte di salita del segnale nell' encoder1A (RISING)
void handleEncoder()
{
  Serial.print(millis());
  Serial.print(",");
  Serial.println(digitalRead(PIN_ENC_B));
}
