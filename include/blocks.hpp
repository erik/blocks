#ifndef _BLOCKS_H_
#define _BLOCKS_H_

#include "SFML/Graphics.hpp"


enum GameState {
  State_InGame,
  State_InMenu,
  State_InPause,
  State_Closed
} ;

bool pointIntersectsShape(int x, int y, sf::Shape shape);
#endif /* _BLOCKS_H_ */
