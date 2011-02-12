#include <iostream>
#include "game.hpp"
#include "world.hpp"

int main() {  
 
  Game* game = Game::Instance();  
  game->Loop();

  return 0;
}
