//
// Game class - contains parameters of a single game.
//
#include "Game.hpp"

Game::Game() {
}

Game::Game(std::string n) {
  str_name = n;
}

std::string Game::name() {
  return str_name;
}

void Game::name(std::string n) {
  str_name = n;
}
