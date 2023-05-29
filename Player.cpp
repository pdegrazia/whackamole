#include "Arduino.h"
#include "Player.h"
#include "Button.h"

Player::Player(uint8_t ledPins[], uint8_t analogPin){
  this->score = 0;
  this->_currentAnimationLed = 0;
  this->_previousMillis = 0;
  this->_interval = 100;
  init(ledPins, analogPin);
};

void Player::init(uint8_t pins[], uint8_t analogPin){
  for (int i=0; i<5; i++){
    this->_buttons[i] = Button(pins[i], analogPin);
  }
}

Button* Player::getButtons(){
  return this->_buttons;
}

void Player::turnOnAllButtons(){
  for (int i=0; i<5; i++){
    this->_buttons[i].ledOn();
  }
}

void Player::playIdleAnimation(){
    this->getButtons()[this->_currentAnimationLed].ledOn();
    unsigned long currentMillis = millis();

    if (currentMillis - this->_previousMillis >= this->_interval){
      this->_previousMillis = currentMillis;
      this->getButtons()[this->_currentAnimationLed].ledOff();
      this->_currentAnimationLed++;
    }

    //I have hardcoded the size of the array here, should make it more dynamic
    //I am basically saying
    //if the next animation led has index bigger than the array
    //reset index to zero
    //I'm sure there is a more elegant way to do that
    if (this->_currentAnimationLed == 5){
      this->_currentAnimationLed = 0;
    }
}

void Player::clearLeds(){
  for (int i=0; i<5; i++){
    this->_buttons[i].ledOff();
  }
}

void Player::randomLedOn(){
    int tempPinOn = random(0,5);
    while(tempPinOn == this->_currentLedOn){
      tempPinOn = random(0,5);
    }
    this->_buttons[this->_currentLedOn].ledOff();
    this->_currentLedOn = tempPinOn;
    this->_buttons[this->_currentLedOn].ledOn();
}

int Player::getButtonPressed(int buttonValue){
  switch (buttonValue){
    case 890 ... 930:
      return 0;
      break;
    case 410 ... 430:
      return 1;
      break;
    case 250 ... 280:
      return 2;
      break;
    case 90 ... 120:
      return 3;
      break;
    case 160 ... 190:
      return 4;
      break;
    default:
      return 99;
      break;
  }
}

int Player::getButtonPressedTwo(int buttonValue){
  switch (buttonValue){
    case 890 ... 930:
      return 0;
      break;
    case 490 ... 510:
      return 1;
      break;
    case 360 ... 390:
      return 2;
      break;
    case 200 ... 220:
      return 3;
      break;
    case 290 ... 310:
      return 4;
      break;
    default:
      return 99;
      break;
  }
}


int Player::getCurrentLedOn(){
  return this->_currentLedOn;
}