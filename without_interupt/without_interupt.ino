/*
  example to drive 2 EC11 rotary encoder using the min amount of pins
*/

const byte chan1pin = 15;
const byte rot1Apin = 2;
const byte rot1Bpin = 3;
const byte rot2Apin = 4;
const byte rot2Bpin = 5;

const byte input1pin = 10;
const byte input2pin = 6;


void setup() {
  // chanels
  pinMode(chan1pin, OUTPUT);

  // EC11 rotary encoder
  pinMode(rot1Apin, INPUT_PULLUP);
  pinMode(rot1Bpin, INPUT_PULLUP);
  pinMode(rot2Apin, INPUT_PULLUP);
  pinMode(rot2Bpin, INPUT_PULLUP);
  pinMode(input1pin, INPUT_PULLUP);
  pinMode(input2pin, INPUT_PULLUP);
}

bool previousRot1AState = LOW;
bool previousRot2AState = LOW;
bool previous1State = LOW;
bool previous2State = LOW;

int counter1 = 50;
int counter2 = 50;

// the loop function runs over and over again forever
void loop() {
  // enable chan1
  digitalWrite(chan1pin, LOW);

  // but1
  bool but1State = digitalRead(input1pin);
  if (!but1State && previous1State) {
    Serial.println("but1");
  }
  previous1State = but1State;

  // but1
  bool but2State = digitalRead(input2pin);
  if (!but2State && previous2State) {
    Serial.println("but2");
  }
  previous2State = but2State;

  // rot1
  bool rot1AState = digitalRead(rot1Apin);
  if (!rot1AState && previousRot1AState) {
    bool rot1BState = digitalRead(rot1Bpin);
    if (rot1BState) {
      counter1++;
    } else {
      counter1--;
    }
    Serial.print("counter1 ");
    Serial.println(counter1);
  }
  previousRot1AState = rot1AState;

  // rot2
  bool rot2AState = digitalRead(rot2Apin);
  if (!rot2AState && previousRot2AState) {
    bool rot2BState = digitalRead(rot2Bpin);
    if (rot2BState) {
      counter2++;
    } else {
      counter2--;
    }
    Serial.print("counter2 ");
    Serial.println(counter2);
  }
  previousRot2AState = rot2AState;

  delay(1);
}
