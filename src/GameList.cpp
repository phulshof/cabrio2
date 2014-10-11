//
// GameList - singleton containing all games we know about.
//
#include "GameList.hpp"

void GameList::add(Game& g) {
  games.push_back(g);
}

void GameList::reset() {
  position = 0;
}

Game& GameList::first() {
  this->reset();
  return this->next();
}

Game& GameList::next() {
  position++;

  if ( position > games.size() - 1 ) {
    this->reset();
  }

  return games.at(position);
}

Game& GameList::previous() {
  if ( position == 0 ) {
    position = games.size() - 1;
  }
  else {
    position--;
  }

  return games.at(position);
}
