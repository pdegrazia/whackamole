#ifndef Button_h
#define Button_h
#include "Arduino.h"
class Button{
  public:
    Button();
    Button(uint8_t ledPin, uint8_t pushPin);
    Button(uint8_t ledPin);
    void ledOn();
    void ledOff();
    // bool isOn();
    // bool isCurrentAnimationLed();
    bool isPressed();
    bool lastPressedState;
    unsigned long lastDebounceTime;
    unsigned long debounceDelay;
  private:
    uint8_t _ledPin;
    uint8_t _pushPin;
    void init();
    // bool _iscurrentAnimationLed;
    // bool _isOn;
};
#endif