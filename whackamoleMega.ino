// includes for df mini player
#include "Arduino.h"
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"


// includes for led matrix
#include <MD_Parola.h>
#include <MD_MAX72xx.h>
#include <SPI.h>

// initialize df player
SoftwareSerial mySoftwareSerial(6, 7); // RX, TX
DFRobotDFPlayerMini myDFPlayer;

// initialize screen
#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define MAX_DEVICES 4

// these pins are only placeholders, must change them to match configuration
#define CLK_PIN   52
#define DATA_PIN  51
#define CS_PIN    53

MD_Parola P = MD_Parola(HARDWARE_TYPE, DATA_PIN, CLK_PIN, CS_PIN, MAX_DEVICES);

int score = 0;

struct button {
  int pressPin;
  int ledPin;
};

struct player {
  int pins[5];
  int size;
  int currentAnimationLed;
  bool started;
  int pinOn;
};

button startButtonSinglePlayer = {10, 11};
button startButtonTwoPlayers = {20, 21};

int buttonValue;

unsigned long previousMillis = 0;

unsigned int timer = 60000;

unsigned long startTimer;

const long interval = 100;

player pOne = {
  {22, 23, 24, 25, 26},
  5,
  0,
  false,
  0
};

player pTwo = {
  {41, 42, 43, 44, 45},
  5,
  0,
  false,
  0
};

void initMusic(){
  if (!myDFPlayer.begin(mySoftwareSerial)) {  //Use softwareSerial to communicate with mp3.
    while(true);
  }
  // Serial.println(F("DFPlayer Mini online."));

  myDFPlayer.setTimeOut(500); //Set serial communictaion time out 500ms

  // // //----Set volume----
  myDFPlayer.volume(10);  //Set volume value (0~30).

  myDFPlayer.outputDevice(DFPLAYER_DEVICE_SD);
  myDFPlayer.EQ(DFPLAYER_EQ_NORMAL);
  myDFPlayer.loop(4);  //Loop the first mp3
  delay(1000);
}

void setup() {
  mySoftwareSerial.begin(9600);
  Serial.begin(115200);
  P.begin();
  // ledMatrix.begin();

  for (int i=0; i<pOne.size; i++){
    pinMode(pOne.pins[i], OUTPUT);
  }
  pinMode(startButtonSinglePlayer.ledPin, OUTPUT);

  digitalWrite(startButtonSinglePlayer.ledPin, HIGH);
  pinMode(startButtonSinglePlayer.pressPin, INPUT_PULLUP);

  for (int i=0; i<pTwo.size; i++){
    pinMode(pTwo.pins[i], OUTPUT);
    digitalWrite(pTwo.pins[i], HIGH);
  }
  pinMode(startButtonTwoPlayers.ledPin, OUTPUT);

  digitalWrite(startButtonTwoPlayers.ledPin, HIGH);
  pinMode(startButtonTwoPlayers.pressPin, INPUT_PULLUP);


  randomSeed(analogRead(0));


  // initMusic();
  P.print("hello");
  // if (!myDFPlayer.begin(mySoftwareSerial)) {  //Use softwareSerial to communicate with mp3.
  //   while(true);
  // }
  // // Serial.println(F("DFPlayer Mini online."));

  // myDFPlayer.setTimeOut(500); //Set serial communictaion time out 500ms

  // // // //----Set volume----
  // myDFPlayer.volume(10);  //Set volume value (0~30).

  // myDFPlayer.outputDevice(DFPLAYER_DEVICE_SD);
  // myDFPlayer.EQ(DFPLAYER_EQ_NORMAL);
  // myDFPlayer.loop(4);  //Loop the first mp3
  // delay(1000);
}

void loop() {
  if (!pOne.started){
    //lights animation
    idle();
    pOne.started = isStartPressed();
    //here insert code for scrolling text
  } else {

    if ((millis() - startTimer) < timer){

      buttonValue = analogRead(A7);
      if (buttonValue > 0)
        if (pOne.pinOn == getButtonPressed(buttonValue)){
          // myDFPlayer.play(1);
          digitalWrite(pOne.pins[pOne.pinOn], LOW);
          randomLightButton(1);
          score++;
        } else {
          // myDFPlayer.play(2);
        }
        P.print(score);
      } else {
        pOne.started = false;
        score = 0;
      }
    }
}

void clearLeds(){
  for (int i=0; i<5; i++){
    digitalWrite(pOne.pins[i], LOW);
  }
}

bool isStartPressed(){
  bool playerOneStarted = digitalRead(startButtonSinglePlayer.pressPin) == false;
  if (playerOneStarted){
    // myDFPlayer.stop();
    clearLeds();
    randomLightButton(1);
    startTimer = millis();
  }
  return playerOneStarted;
}

// this is the function I am running before the game starts
void idle(){
  digitalWrite(pOne.pins[pOne.currentAnimationLed], HIGH);
  digitalWrite(pTwo.pins[pTwo.currentAnimationLed], HIGH);
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval){
    previousMillis = currentMillis;
    digitalWrite(pOne.pins[pOne.currentAnimationLed], LOW);
    pOne.currentAnimationLed++;
    digitalWrite(pTwo.pins[pTwo.currentAnimationLed], LOW);
    pTwo.currentAnimationLed++;
  }

  if (pOne.currentAnimationLed == pOne.size){
    pOne.currentAnimationLed = 0;
  }

  if (pTwo.currentAnimationLed == pTwo.size){
    pTwo.currentAnimationLed = 0;
  }


}


int getButtonPressed(int buttonValue){
  switch (buttonValue){
    case 1003 ... 1005:
      delay(50);
      return 0;
      break;
    case 1013 ... 1015:
      delay(50);
      return 1;
      break;
    case 991 ... 993:
      delay(50);
      return 2;
      break;
    case 978 ... 979:
      delay(50);
      return 3;
      break;
    case 973 ... 975:
      delay(50);
      return 4;
      break;
    default:
      break;
  }
}

void randomLightButton(int player){
  int index = random(0,5);
  int randomPin = pOne.pins[index];
  digitalWrite(randomPin, HIGH);
  pOne.pinOn = index;
}
