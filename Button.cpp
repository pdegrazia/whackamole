#include "Arduino.h"
#include "Button.h"

// empty constructor, does nothing
Button::Button(){
}

Button::Button(uint8_t ledPin){
  this->_ledPin = ledPin;
  this->init();
}

Button::Button(uint8_t ledPin, uint8_t pushPin){
  this->_ledPin = ledPin;
  this->_pushPin = pushPin;
  this->lastPressedState = false;
  this->lastDebounceTime = 0;
  this->debounceDelay = 50;
  // this->_iscurrentAnimationLed = false;
  this->init();
}

void Button::init(){
  pinMode(this->_ledPin, OUTPUT);
  pinMode(this->_pushPin, INPUT_PULLUP);
}

void Button::ledOn(){
  digitalWrite(this->_ledPin, HIGH);
}

void Button::ledOff(){
  digitalWrite(this->_ledPin, LOW);
}

// bool Button::isOn(){
//   return this->_isOn;
// }

// bool Button::isCurrentAnimationLed(){
//   return this->_iscurrentAnimationLed;
// }

bool Button::isPressed(){
  bool isPressed = digitalRead(this->_pushPin);
  return (isPressed == LOW);
}