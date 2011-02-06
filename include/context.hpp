#ifndef _CONTEXT_H_
#define _CONTEXT_H_

#include "blocks.hpp"
#include "input.hpp"
#include "window.hpp"
#include "gui.hpp"
#include "world.hpp"
#include "scene.hpp"

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <iostream>

struct InputHandler;
enum GameState;
struct GUIPage;
class Scene;

struct Context {
  Window *window;
  GameState gameState;
  InputHandler *input;
  float frameRate;
  GUIPage *gui;
  World world;
  Scene* scene;

  Context() : gameState(State_InMenu) {}
  Context(Window* w) : window(w), gameState(State_InMenu),
                                 frameRate(0.0f) {}

  void HandleInput();
  void Render();

  // Initialize everything needed for the game
  static void Init();

private:
  void RenderState();

} ;

#endif /* _CONTEXT_H_ */
