#ifndef Button_h
#define Button_h
#include "Arduino.h"
class Button{
  public:
    void turnOn();
    void turnOff();
  private:
    uint8_t ledPin;
    uint8_t pushPin;
}
#endif