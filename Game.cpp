#include "Arduino.h"

#include "Game.h"
Game::Game() {
  this->_gameStarted = false;
  this->maxScore = 100;
  this->gameTimeout = 4000; //this is only 4 secs for the time being, increase it
}

bool Game::isGameStarted(){
  return this->_gameStarted;
}

uint8_t Game::getGameType(){
  return this->_gameType;
}

void Game::setGameType(uint8_t gameType){
  this->_gameType = gameType;
}

