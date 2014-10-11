//
// One day, there will be some code here.
//
#include "GameList.hpp"

int main(int argc, char* argv[]) {
  GameList& list = GameList::get_instance();
  Game g;

  list.add(g);

  return 0;
}
