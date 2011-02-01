#ifndef _CONTEXT_H_
#define _CONTEXT_H_

#include "blocks.hpp"
#include "input.hpp"
#include "window.hpp"
#include "gui.hpp"

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <iostream>

struct InputHandler;
enum GameState;

struct Context {
  Window *window;
  GameState gameState;
  InputHandler *input;
  float frameRate;
  GUIPage gui;

  Context() : gameState(State_InMenu) {}
  Context(Window* w) : window(w), gameState(State_InMenu),
                                 frameRate(0.0f) {}

  void HandleInput();
  void Render();

  // Initialize everything needed for the game
  static void Init();

} ;

#endif /* _CONTEXT_H_ */
