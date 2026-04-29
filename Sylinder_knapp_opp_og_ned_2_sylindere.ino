const int knapp1_opp = 6;
const int knapp1_ned = 7;
const int knapp2_opp = 12;
const int knapp2_ned = 13;
const int rele1Input1 = 9;//rele styrer aktuaktoren
const int rele1Input2 = 8;
const int rele2Input1 = 11;//rele styrer aktuaktoren
const int rele2Input2 = 10;
const int lys = 2;

void setup() {
  pinMode(knapp1_opp, INPUT_PULLUP);
  pinMode(knapp1_ned, INPUT_PULLUP);
  pinMode(knapp2_opp, INPUT_PULLUP);
  pinMode(knapp2_ned, INPUT_PULLUP);
  pinMode(rele1Input1, OUTPUT);
  pinMode(rele1Input2, OUTPUT);
  pinMode(rele2Input1, OUTPUT);
  pinMode(rele2Input2, OUTPUT);

  digitalWrite(rele1Input1, HIGH);
  digitalWrite(rele1Input2, HIGH);
  digitalWrite(rele2Input1, HIGH);
  digitalWrite(rele2Input2, HIGH);

  pinMode(lys, OUTPUT);
  digitalWrite(lys, HIGH);
}

void loop(){

  // Aktuator 1 går opp (knapp_opp trykka = LOW)
  if(digitalRead(knapp1_opp) == LOW && digitalRead(knapp1_ned) == HIGH && digitalRead(knapp2_ned) == HIGH && digitalRead(knapp2_opp) == HIGH){
    digitalWrite(rele1Input1, HIGH);
    digitalWrite(rele1Input2, LOW);
  }

  // Aktuator går ned (knapp_ned trykka = LOW)
  else if(digitalRead(knapp1_opp) == HIGH && digitalRead(knapp1_ned) == LOW && digitalRead(knapp2_ned) == HIGH && digitalRead(knapp2_opp) == HIGH){
    digitalWrite(rele1Input1, LOW);
    digitalWrite(rele1Input2, HIGH);
  }

  // Ingen knapp trykka → stopp
  else{
    digitalWrite(rele1Input1, HIGH);
    digitalWrite(rele1Input2, HIGH);
  }



  // Aktuator 2 går opp (knapp_opp trykka = LOW)
  if(digitalRead(knapp2_opp) == LOW && digitalRead(knapp2_ned) == HIGH && digitalRead(knapp1_ned) == HIGH && digitalRead(knapp1_opp) == HIGH){
    digitalWrite(rele2Input1, HIGH);
    digitalWrite(rele2Input2, LOW);
  }

  // Aktuator går ned (knapp_ned trykka = LOW)
  else if(digitalRead(knapp2_opp) == HIGH && digitalRead(knapp2_ned) == LOW && digitalRead(knapp1_ned) == HIGH && digitalRead(knapp1_opp) == HIGH){
    digitalWrite(rele2Input1, LOW);
    digitalWrite(rele2Input2, HIGH);
  }

  // Ingen knapp trykka → stopp
  else{
    digitalWrite(rele2Input1, HIGH);
    digitalWrite(rele2Input2, HIGH);
  }
}