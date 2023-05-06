#ifndef Button_h
#define Button_h
#include "Arduino.h"
class Button{
  public:
    // void turnOn();
    // void turnOff();
    Button(uint8_t _ledPin, uint8_t _pushPin);
  private:
    uint8_t _ledPin;
    uint8_t _pushPin;
    void init();
};
#endif