#include <Servo.h>

// Pins for stoppeklokke-displayet (hovedtid)
const int DS_pin = 8;
const int SHCP_pin = 9;
const int STCP_pin = 10;
const int RESET_sensor = A2;

// Pins for idealtid-displayet
const int DS_pin_it = 5;
const int SHCP_pin_it = 6;
const int STCP_pin_it = 7;
const int idealtid_knapp = 2;
const int start_knapp = 3;

// Servo-konfigurasjon
Servo myServo;
const int servoPin = 4;

// lyssensorens terskel
const int THRESHOLD = 100;

// Tall for 7-segment display
int dec_digits[10] = {1, 79, 18, 6, 76, 36, 32, 15, 0, 4};

// Variabler for timing og tilstand
bool running = false;
unsigned long startTime = 0;
unsigned long elapsedTime = 0;
unsigned long idealTid = 0;
unsigned long servoOpenTime = 0;

// For å oppdage knappetrykk (edge detection)
bool lastButtonState = HIGH;
bool lastStartState = HIGH;

// tidsverdier på stoppeklokke-displayet
void displayTime(unsigned long ms) {
  int hundredths = (ms / 10) % 10;
  int tenths     = (ms / 100) % 10;
  int seconds    = (ms / 1000) % 10;
  int tensecs    = (ms / 10000) % 10;

  digitalWrite(STCP_pin, LOW);
  shiftOut(DS_pin, SHCP_pin, MSBFIRST, dec_digits[hundredths]);
  shiftOut(DS_pin, SHCP_pin, MSBFIRST, dec_digits[tenths]);
  shiftOut(DS_pin, SHCP_pin, MSBFIRST, dec_digits[seconds]);
  shiftOut(DS_pin, SHCP_pin, MSBFIRST, dec_digits[tensecs]);
  digitalWrite(STCP_pin, HIGH);
}

// Viser idealtid på ideal-display
void displayIdeal(unsigned long ms) {
  int hundredths = (ms / 10) % 10;
  int tenths     = (ms / 100) % 10;
  int seconds    = (ms / 1000) % 10;
  int tensecs    = (ms / 10000) % 10;

  digitalWrite(STCP_pin_it, LOW);
  shiftOut(DS_pin_it, SHCP_pin_it, MSBFIRST, dec_digits[hundredths]);
  shiftOut(DS_pin_it, SHCP_pin_it, MSBFIRST, dec_digits[tenths]);
  shiftOut(DS_pin_it, SHCP_pin_it, MSBFIRST, dec_digits[seconds]);
  shiftOut(DS_pin_it, SHCP_pin_it, MSBFIRST, dec_digits[tensecs]);
  digitalWrite(STCP_pin_it, HIGH);
}

void setup() {
  // Setter opp utganger for display
  pinMode(STCP_pin, OUTPUT);
  pinMode(SHCP_pin, OUTPUT);
  pinMode(DS_pin, OUTPUT);
  pinMode(STCP_pin_it, OUTPUT);
  pinMode(SHCP_pin_it, OUTPUT);
  pinMode(DS_pin_it, OUTPUT);
  
  // Knapper med intern pullup
  pinMode(idealtid_knapp, INPUT_PULLUP);
  pinMode(start_knapp, INPUT_PULLUP);
  
  // servoens lukkede posisjon på 50 grader
  myServo.attach(servoPin);
  myServo.write(50);
  
  Serial.begin(50000);
  displayTime(0);

  // Bruk støy fra analog pin til tilfeldig generator
  randomSeed(analogRead(A1));
}

void loop() {
  int resetLight = analogRead(RESET_sensor);

  // Start-Logikk
  bool startState = digitalRead(start_knapp);
  if (startState == LOW && lastStartState == HIGH && !running) {
    myServo.write(0);          // Åpne port umiddelbart
    delay(40);                 // kula ruller ikke med en gang -> legger på et lite delay før timeren begynner
    running = true;            // Start tidtaking
    startTime = millis();
    elapsedTime = 0;
    servoOpenTime = millis();  // Lagre tidspunkt for åpning
  }
  lastStartState = startState;

  // LUKK PORT etter 4 sekunder (uten å stoppe programmet)
  if (servoOpenTime > 0 && millis() - servoOpenTime >= 4000) {
    myServo.write(50);
    servoOpenTime = 0;
  }

  // Stopp-Logikk (lyssensor trigger)
  if (resetLight < THRESHOLD && running) {
    running = false;
    delay(200); // liten debounce
  }

  // Oppdater tiden
  if (running) {
    elapsedTime = millis() - startTime;

    // Stopp automatisk etter 15 sekunder
    if (elapsedTime >= 15000UL) {
      running = false;
    }
  }
  displayTime(elapsedTime);

  // Generer Idealtid ved knappetrykk
  bool buttonState = digitalRead(idealtid_knapp);
  if (buttonState == LOW && lastButtonState == HIGH) {
    idealTid = random(950, 1800); // tilfeldig tid som har øvre og nedre grense av hva som er mulig på rullebanen
    delay(200); // debounce
  }
  lastButtonState = buttonState;
  displayIdeal(idealTid);

  // Debugging i Serial Monitor
  Serial.print("Kjører: "); Serial.print(running);
  Serial.print(" | Tid: "); Serial.println(elapsedTime);
  Serial.print(" | Sensorverdi: "); Serial.println(resetLight);
}