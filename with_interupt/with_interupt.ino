/*
  example to drive 2 potentiometers and 2 EC11 rotary encoder using the min amount of pins ans interupts
*/

const byte chan1pin = 14;
const byte chan2pin = 16;
const byte rotApin = 7;
const byte rotBpin = 8;
const byte rot2Apin = 3;
const byte rot2Bpin = 4;

void setup() {
  // chanels
  pinMode(chan1pin, OUTPUT);
  pinMode(chan2pin, OUTPUT);

  // EC11 rotary encoder
  pinMode(rotApin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(rotApin), rotary1function, FALLING);
  pinMode(rotBpin, INPUT_PULLUP);

  pinMode(rot2Apin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(rot2Apin), rotary2function, FALLING);
  pinMode(rot2Bpin, INPUT_PULLUP);
}

// rotary encoder
int rotValue = 50;
int previousRotValue = 50;

// potentiometer
const int threshold = 70;
int previousSens1 = 0;
int previousSens2 = 0;

// the loop function runs over and over again forever
void loop() {
  digitalWrite(chan2pin, HIGH);
  digitalWrite(chan1pin, LOW);
  int sensorVal1 = analogRead(10);

  digitalWrite(chan2pin, LOW);
  digitalWrite(chan1pin, HIGH);
  int sensorVal2 = analogRead(10);

  if (previousSens1 - sensorVal1 > threshold || previousSens1 - sensorVal1 < -threshold) {
    Serial.print("potar1 is ");
    Serial.println(sensorVal1);
    previousSens1 = sensorVal1;
  }
  if (previousSens2 - sensorVal2 > threshold || previousSens2 - sensorVal2 < -threshold) {
    Serial.print("potar2 is ");
    Serial.println(sensorVal2);
    previousSens2 = sensorVal2;
  }

  if(rotValue != previousRotValue)
  {
    Serial.print("rotary1 is ");
    Serial.println(rotValue);
    previousRotValue = rotValue;
  }
}

void rotary1function() {
  static uint32_t lastChange = 0;
  if (millis() - lastChange > 60) {
    if (digitalRead(rotBpin)) {
      rotValue++;
    } else {
      rotValue--;
    }
    lastChange = millis();
  }
}

void rotary2function() {
  static uint32_t lastChange = 0;
  if (millis() - lastChange > 60) {
    if (digitalRead(rot2Bpin)) {
      rotValue++;
    } else {
      rotValue--;
    }
    lastChange = millis();
  }
}
