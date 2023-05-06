#ifndef Game_h
#define Game_h

#include "Arduino.h"

class Game {
  public:
    Game();
    bool isGameStarted();
    uint8_t getGameType();
    void setGameType(uint8_t game_type);
    uint8_t maxScore;
    int gameTimeout;
  private:
    bool _gameStarted;
    uint8_t _gameType;
};

#endif