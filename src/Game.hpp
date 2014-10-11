//
// Game class - contains parameters of a single game.
//
#ifndef CABRIO_GAME_HPP_
#define CABRIO_GAME_HPP_

#include <string>

#include "Platform.hpp"

class Game {
  public:
    Game();
    Game(std::string name);

    Platform& platform();
    std::string name();
    void name(std::string n);

  private:
    std::string str_name;
};

#endif
