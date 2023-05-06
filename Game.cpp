#include "Arduino.h"

#include "Game.h"
Game::Game() {
  this->_game_started = false;
  this->maxScore = 100;
  this->gameTimeout = 4000; //this is only 4 secs for the time being, increase it
}

bool Game::is_game_started(){
  return this->_game_started;
}

uint8_t Game::get_game_type(){
  return this->_game_type;
}

void Game::set_game_type(uint8_t game_type){
  this->_game_type = game_type;
}

