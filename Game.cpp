#include "Arduino.h"

#include "Game.h"
Game::Game() {
  this->_started = false;
  this->_maxScore = 100;
  this->_timeout = 4000; //this is only 4 secs for the time being, increase it
}

bool Game::started(){
  return this->_started;
}

uint8_t Game::getGameType(){
  return this->_gameType;
}

void Game::setGameType(uint8_t gameType){
  this->_gameType = gameType;
}

void Game::setStarted(bool started){
  this->_started = started;
}

