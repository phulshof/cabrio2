//
// GameList - singleton containing all games we know about.
//
#ifndef CABRIO_GAMELIST_HPP_
#define CABRIO_GAMELIST_HPP_

#include <vector>

#include "Game.hpp"

class GameList {
  public:
    static GameList& get_instance() {
      static GameList instance;
      return instance;
    }

    void add(Game& g);
    void reset();
    Game& first();
    Game& next();
    Game& previous();

  private:
    GameList() {};
    GameList(GameList const&);
    void operator=(GameList const&);

    std::vector<Game> games;
    size_t position;
};

#endif
