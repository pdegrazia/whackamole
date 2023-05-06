#include "Arduino.h"
#include "Button.h"

Button::Button(uint8_t ledPin, uint8_t pushPin){
  this->ledPin = ledPin;
  this->pushPin = pushPin;
}