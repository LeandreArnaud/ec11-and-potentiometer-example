/*
  example to drive 2 EC11 rotary encoder using the min amount of pins and only 1 interupts
*/

const byte chan1pin = 15;

const byte but1pin = 6;
const byte but2pin = 10;

const byte interuptPin = 7;

const byte rot1Apin = 3;
const byte rot1Bpin = 2;
const byte rot2Apin = 5;
const byte rot2Bpin = 4;

void setup() {
  // chanels
  pinMode(chan1pin, OUTPUT);

  // EC11 rotary encoder
  pinMode(interuptPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interuptPin), rotaryFunction, FALLING);
  
  // inputs
  pinMode(but1pin, INPUT_PULLUP);
  pinMode(but2pin, INPUT_PULLUP);

  pinMode(rot1Apin, INPUT_PULLUP);
  pinMode(rot1Bpin, INPUT_PULLUP);
  pinMode(rot2Apin, INPUT_PULLUP);
  pinMode(rot2Bpin, INPUT_PULLUP);
}

// rotary encoder
int rotValue = 50;
int previousRotValue = 50;

bool previousRot1AState = LOW;
bool previousRot2AState = LOW;

// buttons
bool previousBut1state = LOW;
bool previousBut2state = LOW;

void rotaryFunction() {
  static uint32_t lastChange = 0;
  if (millis() - lastChange > 100) {

    bool rot1AState = digitalRead(rot1Apin);
    if (rot1AState && !previousRot1AState) {
      if (digitalRead(rot1Bpin)) {
        rotValue++;
      } else {
        rotValue--;
      }
    }
    previousRot1AState = rot1AState;

    // bool rot2AState = digitalRead(rot2Apin);
    // if (rot2AState && !previousRot2AState) {
    //   if (digitalRead(rot2Bpin)) {
    //     rotValue++;
    //   } else {
    //     rotValue--;
    //   }
    // }
    // previousRot2AState = rot2AState;

  }
  lastChange = millis();
}

void loop() {
  // enable chan1
  digitalWrite(chan1pin, LOW);

  // read pin1
  bool but1state = digitalRead(but1pin);
  if (!but1state && previousBut1state) {
    Serial.println("button1 pressed");
  }
  previousBut1state = but1state;

  // read pin2
  bool but2state = digitalRead(but2pin);
  if (!but2state && previousBut2state) {
    Serial.println("button2 pressed");
  }
  previousBut2state = but2state;

  // delay(100);

  if(rotValue != previousRotValue)
  {
    Serial.print("rotary is ");
    Serial.println(rotValue);
    previousRotValue = rotValue;
  }
}


