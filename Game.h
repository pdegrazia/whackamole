#ifndef Game_h
#define Game_h

#include "Arduino.h"

class Game {
  public:
    Game();
    bool started();
    uint8_t getGameType();
    void setGameType(uint8_t game_type);
    void setStarted(bool started);
  private:
    uint8_t _maxScore;
    int _timeout;
    bool _started;
    uint8_t _gameType;
};

#endif