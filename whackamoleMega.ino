// includes for df mini player
#include "Arduino.h"
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"

// includes for led matrix
#include <MD_Parola.h>
#include <MD_MAX72xx.h>
#include <SPI.h>

// Custom imports
#include "Game.h"
#include "Button.h"
#include "Player.h"

// initialize df player
// SoftwareSerial mySoftwareSerial(6, 7); // RX, TX
// DFRobotDFPlayerMini myDFPlayer;

// initialize screen
#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define MAX_DEVICES 8

#define CLK_PIN   52
#define DATA_PIN  51
#define CS_PIN    53

MD_Parola P = MD_Parola(HARDWARE_TYPE, DATA_PIN, CLK_PIN, CS_PIN, MAX_DEVICES);

Button startButtonSinglePlayer = Button(21,20);
Button startButtonTwoPlayers = Button(11, 10);

uint8_t playerOnePins[] = {41, 42, 43, 44, 45};
uint8_t playerTwoPins[] = {22, 23, 24, 26, 25};

// uint8_t playerOnePins[] = {22, 23, 24, 26, 25};
// uint8_t playerTwoPins[] = {41, 42, 43, 44, 45};

Player playerOne = Player(playerOnePins,A7);
Player playerTwo = Player(playerTwoPins,A3);

Game game = Game();

int buttonValue;
int playerOneButtonValue;
int playerTwoButtonValue;

uint8_t buttonPressedIndex;

uint8_t playerOneButtonPressedIndex;
uint8_t playerTwoButtonPressedIndex;

unsigned int timer = 15000;

unsigned long startTimer;

unsigned long lastDebounceTime = 0;

unsigned long switchMillis = 0;

const char *messages[] = {
  "Press P1 or P2 button to start",
};

uint8_t zoneWinner;
uint8_t zoneLoser;

uint8_t zoneNumber = 2;

// void initMusic(){
//   if (!myDFPlayer.begin(mySoftwareSerial)) {  //Use softwareSerial to communicate with mp3.
//     while(true);
//   }
//   // Serial.println(F("DFPlayer Mini online."));

//   myDFPlayer.setTimeOut(500); //Set serial communictaion time out 500ms

//   // // //----Set volume----
//   myDFPlayer.volume(10);  //Set volume value (0~30).

//   myDFPlayer.outputDevice(DFPLAYER_DEVICE_SD);
//   myDFPlayer.EQ(DFPLAYER_EQ_NORMAL);
//   myDFPlayer.loop(4);  //Loop the first mp3
//   delay(1000);
// }

void setup() {
  // mySoftwareSerial.begin(9600);
  Serial.begin(9600);
  P.begin(2);
  zoneNumber = 1;
  P.setZone(0,0,7);
  // P.setZone(1,4,7);
  // P.setIntensity(2);
  // pinMode(32, OUTPUT);
  // digitalWrite(32, HIGH);  
  // pinMode(A3, INPUT);
  startButtonSinglePlayer.ledOn();
  startButtonTwoPlayers.ledOn();
    
  playerOne.turnOnAllButtons();
  playerTwo.turnOnAllButtons();  
  
  randomSeed(analogRead(0));

  // initMusic();                               
  
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
  P.displayZoneText(0, messages[0], PA_CENTER, 100, 10, PA_SCROLL_LEFT);
  P.displayReset(0);
}

void loop() {
    if (P.displayAnimate()){
        for (uint8_t i=0; i<zoneNumber; i++){
          if (P.getZoneStatus(i)){
            // do something with the parameters for the animation then reset it
            P.displayReset(i);
          }
        }
    }

  if (!game.started()){
    playerOne.playIdleAnimation();
    playerTwo.playIdleAnimation();
    
    if (startButtonSinglePlayer.isPressed()){
      game.setStarted(true);
      game.setGameType(1);

      char score1[80];
      sprintf(score1, "%i", playerOne.score);
      char *chrdisp1[] = {score1};
      P.displayZoneText(0, chrdisp1[0], PA_LEFT, 0, 0, PA_PRINT, PA_NO_EFFECT);
      P.displayReset(0);
      // if (P.displayAnimate()){
      //   for (uint8_t i=0; i<2; i++)
      //   {
      //     if (P.getZoneStatus(i))
      //     {
      //       // do something with the parameters for the animation then reset it
      //       P.displayReset(i);
      //     }
      //   }
      // }

      // if (P.displayAnimate()) {
      //   P.displayReset();
      // }
      //turn off all leds for player1      
      playerOne.clearLeds();
      //turn on all leds for player 2
      playerTwo.turnOnAllButtons();
      //print message on screen for player one
      startTimer = millis(); 
      playerOne.randomLedOn();
    }
    if (startButtonTwoPlayers.isPressed()){
      game.setStarted(true);
      game.setGameType(2);
      playerOne.clearLeds();
      playerTwo.clearLeds();
      playerOne.randomLedOn();
      playerTwo.randomLedOn();

      P.setZone(0,0,3);
      P.setZone(1,4,7);
      zoneNumber = 2;

      char score1[80];
      sprintf(score1, "%d", playerOne.score);
      char *chrdisp1[] = {score1};

      char score2[80];
      sprintf(score2, "%d", playerTwo.score);
      char *chrdisp2[] = {score2};

      P.displayZoneText(1,chrdisp1[0], PA_RIGHT, 0, 0, PA_PRINT, PA_NO_EFFECT);
      P.displayZoneText(0,chrdisp2[0], PA_RIGHT, 0, 0, PA_PRINT, PA_NO_EFFECT);
      P.displayReset(0);
      P.displayReset(1);
      // if (P.displayAnimate()){
      //   for (uint8_t i=0; i<2; i++){
      //     if (P.getZoneStatus(i)){
      //       // do something with the parameters for the animation then reset it
      //         P.displayReset(i);
      //     }
      //   }
      // }
    }
  }

  if (game.getGameType() == 1 && game.started()){
      if ((millis() - startTimer) < timer){
        buttonValue = analogRead(A8);
        if (buttonValue > 0){

          if (millis() - switchMillis >= 50){
            switchMillis = millis();            
            buttonPressedIndex = playerOne.getButtonPressed(buttonValue);
            if (buttonPressedIndex == playerOne.getCurrentLedOn()){
                playerOne.randomLedOn();
                playerOne.score++;
                char score1[80];
                sprintf(score1, "%d", playerOne.score);
                char *chrdisp1[] = {score1};
                P.displayZoneText(0, chrdisp1[0], PA_LEFT, 0, 0, PA_NO_EFFECT);
                P.displayReset(0);
                // if (P.displayAnimate()){
                //  for (uint8_t i=0; i<2; i++){
                //     if (P.getZoneStatus(i)){
                //   // do something with the parameters for the animation then reset it
                //       P.displayReset(i);
                //     }
                //   }
                // }      
              }
            }
          }      
      } else {
        playerOne.turnOnAllButtons();
        // P.displayAnimate();
        if (startButtonSinglePlayer.isPressed()){
          if (millis() - switchMillis >= 100){
            switchMillis = millis();  
            delay(1000);
            game.setStarted(false);
            game.setGameType(0);
            playerOne.score = 0;
            P.setZone(0, 0, 7);
            P.displayZoneText(0, "Press P1 or P2 button to start", PA_CENTER, 100, 10, PA_SCROLL_LEFT);
            P.displayReset(0);
            // if (P.displayAnimate()){
            //   for (uint8_t i=0; i<2; i++){
            //     if (P.getZoneStatus(i)){
            //       // do something with the parameters for the animation then reset it
            //       P.displayReset(i);
            //     }
            //   }
            // }

            // if (P.displayAnimate()){
            // P.displayReset();  
            // }
          }         
        }
      }
  }
      
  if (game.getGameType()==2 && game.started()) {
    if ( playerOne.score < 5 && playerTwo.score < 5){
        playerOneButtonValue = analogRead(A8);
        playerTwoButtonValue = analogRead(A5);
        if (millis() - switchMillis >= 50){
          switchMillis = millis();
          playerOneButtonPressedIndex = playerOne.getButtonPressed(playerOneButtonValue);
          playerTwoButtonPressedIndex = playerTwo.getButtonPressed(playerTwoButtonValue);
          if (playerOneButtonPressedIndex == playerOne.getCurrentLedOn()){
            playerOne.randomLedOn();
            playerOne.score++;
          }
          if (playerTwoButtonPressedIndex == playerTwo.getCurrentLedOn()){
            playerTwo.randomLedOn();
            playerTwo.score++;
          }
        }
        char score1[80];
        sprintf(score1, "%d", playerOne.score);
        char *chrdisp1[] = {score1};

        char score2[80];
        sprintf(score2, "%d", playerTwo.score);
        char *chrdisp2[] = {score2};                  

        P.displayZoneText(1,chrdisp1[0], PA_CENTER, 0, 0, PA_PRINT, PA_NO_EFFECT);
        P.displayZoneText(0,chrdisp2[0], PA_CENTER, 0, 0, PA_PRINT, PA_NO_EFFECT);
        P.displayReset(0);
        P.displayReset(1);
        // if (P.displayAnimate()){
        //   for (uint8_t i=0; i<2; i++){
        //     if (P.getZoneStatus(i)){
        //       // do something with the parameters for the animation then reset it
        //       P.displayReset(i);
        //     }
        //   }
        // }
    } else {
      
      if (playerOne.score > playerTwo.score){
        zoneWinner = 1;
        zoneLoser = 0;
      }
      if (playerOne.score < playerTwo.score){
        zoneWinner = 0;
        zoneLoser = 1;
      }
      P.displayZoneText(zoneWinner,"1ST", PA_CENTER, 0, 0, PA_PRINT, PA_NO_EFFECT);
      P.displayZoneText(zoneLoser,"2ND", PA_CENTER, 0, 0, PA_PRINT, PA_NO_EFFECT);
      P.displayReset(0);
      P.displayReset(1);     
      // if (P.displayAnimate()){
      //   for (uint8_t i=0; i<2; i++)
      //   {
      //     if (P.getZoneStatus(i))
      //     {
      //       // do something with the parameters for the animation then reset it
      //       P.displayReset(i);
      //     }
      //   }
      // }
      if (startButtonSinglePlayer.isPressed()){
        if (millis() - switchMillis >= 50){
          switchMillis = millis();  
          delay(1000);
          game.setGameType(0);
          game.setStarted(false);
          playerOne.score = 0;
          playerTwo.score = 0;
          // P.displayClear();
          // P.begin();
          zoneNumber=1;
          P.setZone(0, 0, 7);
          P.displayZoneText(0, "Press P1 or P2 button to start", PA_CENTER, 100, 10, PA_SCROLL_LEFT);
          P.displayReset(0);
          // delay(1000);
          // P.displayReset(0);
          // if (P.displayAnimate()){
          //   for (uint8_t i=0; i<1; i++){
          //     if (P.getZoneStatus(i)){
          //       // do something with the parameters for the animation then reset it
          //       P.displayReset(i);
          //     }
          //   }
          // }
          // if (P.displayAnimate()){
          //   P.displayReset();  
          // }
        }
      }
    } 
  }      
}