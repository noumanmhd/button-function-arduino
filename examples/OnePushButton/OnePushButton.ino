#include <buttonfunc.h>

ButtonFunction button(A2);

bool state = LOW;

void setup() {
  Serial.begin(9600);

  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, state);

  // Initialize button on Low Active with Pullup Resistor
  button.begin(LOW);

  // On Two Tap
  button.attachTap(sayHi, 2);
  // On One Long Press
  button.attachLongPress(toggleLed, 1);
  // On Two Tap and One Long Press
  button.attachTapAndPress(sendDuration, 2, 1);
}

void loop() {
  button.scan();
  // Your Code here
}

void sayHi() { 
    Serial.println("Hi"); 
}

void toggleLed() {
  state = !state;
  digitalWrite(LED_BUILTIN, state);
}

void sendDuration(){
    Serial.println(millis());
}