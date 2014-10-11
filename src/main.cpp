//
// One day, there will be some code here.
//
#include <iostream>
using namespace std;

#include "GameList.hpp"

int main(int argc, char* argv[]) {
  GameList& list = GameList::get_instance();

  Game g1("Hello");
  Game g2("Goodbye");

  list.add(g1);
  list.add(g2);

  cout << list.first().name() << endl;
  cout << list.next().name() << endl;
  cout << list.next().name() << endl;

  list.reset();
  cout << list.first().name() << endl;
  cout << list.previous().name() << endl;
  cout << list.previous().name() << endl;

  return 0;
}
