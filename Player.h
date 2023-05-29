#ifndef Player_h
#define Player_h

#include "Arduino.h"
#include "Button.h"

class Player{
  public:
    Player();
    Player(uint8_t ledPins[], uint8_t analogPin);
    uint8_t score;
    Button* getButtons();
    // Button getButton(uint8_t index);
    void turnOnAllButtons();
    void playIdleAnimation();
    void clearLeds();
    void randomLedOn();
    int getButtonPressed(int buttonValue);
    int getButtonPressedTwo(int buttonValue);
    int getCurrentLedOn();
  private:
    void init(uint8_t pins[], uint8_t analogPin);
    Button _buttons[5];
    uint8_t _currentAnimationLed;
    unsigned long _previousMillis;
    uint8_t _interval;
    int _currentLedOn;
};
#endif