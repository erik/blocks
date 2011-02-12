#ifndef _BLOCKS_H_
#define _BLOCKS_H_

#include "SFML/Graphics.hpp"


enum GameState {
  State_InGame,
  State_InMenu,
  State_Paused,
  State_GameOver,
  State_Closed
} ;


/* stolen from Arduino, maps number in range (a..b) into range (x..y) */
long map(long x, long in_min, long in_max, long out_min, long out_max);

#endif /* _BLOCKS_H_ */
