#ifndef _GAME_H_
#define _GAME_H_

#include "blocks.hpp"
#include "context.hpp"
#include "window.hpp"
#include "gui.hpp"

// Singleton class

class GUIPage;

struct Game {
  Context* context;
  Window* win;
  GUIPage* gui;

  void Loop();
  void Close();

  static Game* Instance();

  void CreateGame();

private:
  Game() {}
  Game(Game const&){};

  void CreateMenu();

  static Game* Create();

  static Game* instance;
};

#endif /* _GAME_H_ */
