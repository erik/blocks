#include <iostream>
#include "game.hpp"
#include "world.hpp"

int main() {  
 
  Game* game = Game::Instance();  
  game->Loop();

  return 0;
}


// Move shapes left/right, rotate. 
// after 5 seconds, piece automatically falls
// countdown apears onscreen, smaller than in the ascii, but still significant

///////////////////////////////////////////////////////////////
//  SCORE: 1000      <<<       /#\        >>>                //
//                 <<<<<<<<<< /###\ >>>>>>>>>>>              //
//                   <<<     /#####\      >>>                //
//                                                           //
//                                                           //
//        |-[                 555555555                      //
//        |                   555555555                      //
//        |                   5555                           //  
//  10    |                   5555                           //  
// meters!|                   5555555                        //  
//        |                        555                       //  
//        |                         555    ...   ...   ...   //  
//        |                        555    ..... ..... ...... //  
//        |-[                 5555555      ...   ...   ...   //  
//            ==================================             //  
//                                                           //  
//                                                           //  
//                                                           //  
//                                                           //  
///////////////////////////////////////////////////////////////
