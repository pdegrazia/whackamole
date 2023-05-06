#include "Arduino.h"
#include "Button.h"

Button::Button(uint8_t ledPin, uint8_t pushPin){
  this->_ledPin = ledPin;
  this->_pushPin = pushPin;
}

void Button::init(){
  pinMode(this->_ledPin, OUTPUT);
}
