//
// One day, there will be some code here.
//
#include <iostream>
using namespace std;

#include "GameList.hpp"
#include "Quad.hpp"
#include "Logger.hpp"

int main(int argc, char* argv[]) {
  GameList& list = GameList::get_instance();
  Logger& logger = Logger::get_instance();

  logger.level(LOG_DEBUG);
  logger.log(LOG_INFO, "Starting up");

  Game g1("Hello");
  Game g2("Goodbye");
  Quad q1;
  q1.texture("./share/cabrio_logo.png");

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
