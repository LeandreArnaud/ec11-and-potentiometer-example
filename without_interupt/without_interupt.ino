/*
  example to drive 2 potentiometers and 2 EC11 rotary encoder using the min amount of pins ans interupts
*/

const byte chan1pin = 14;
const byte chan2pin = 16;
const byte rotApin = 2;
const byte rotBpin = 18;

void setup() {
  // chanels
  pinMode(chan1pin, OUTPUT);
  pinMode(chan2pin, OUTPUT);

  // EC11 rotary encoder
  pinMode(rotApin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(rotApin), rotary1function, FALLING);
  pinMode(rotBpin, INPUT_PULLUP);
}

int previousSens1 = 0;
int previousSens2 = 0;
bool previousRotA = digitalRead(rotApin);
int rotValue = 50;
int threshold = 70;

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
}

void rotary1function() {
  // bool rotA = digitalRead(rotApin);
  // if (rotA != previousRotA && rotA) {
  //   if (digitalRead(rotBpin) == rotA) {
  //     rotValue--;
  //   } else {
  //     rotValue++;
  //   }
  //   Serial.print("rotary1 is ");
  //   Serial.println(rotValue);
  // }
  // previousRotA = rotA;
  Serial.println("interupt");
  delay(1000);
}
