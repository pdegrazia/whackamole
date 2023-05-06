#ifndef Game_h
#define Game_h

#include "Arduino.h"

class Game {
  public:
    Game();
    bool is_game_started();
    uint8_t get_game_type();
    void set_game_type(uint8_t game_type);
    uint8_t maxScore;
    int gameTimeout;
  private:
    bool _game_started;
    uint8_t _game_type;
};

#endif