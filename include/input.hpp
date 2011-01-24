#ifndef _INPUT_H_
#define _INPUT_H_

#include "context.hpp"

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

struct Context;

struct InputHandler {
  Context* context;
  sf::Vector2<unsigned int> mouse;
  float lastFrameTime;
  sf::Clock clock;

  InputHandler(Context* c) : context(c), mouse(-1, -1), 
                             lastFrameTime(0.0f), clock() {}
  void HandleInput();
};

#endif /* _INPUT_H_ */
