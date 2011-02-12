#include "game.hpp"

int main() {  
 
  Game* game = Game::Instance();  
  game->Loop();

  return 0;
}
