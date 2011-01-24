#include "input.hpp"

void InputHandler::HandleInput() {
  const sf::Input& input = context->window->App.GetInput();
  sf::Event event;
  
  mouse.x = input.GetMouseX();
  mouse.y = input.GetMouseY();

  lastFrameTime = clock.GetElapsedTime();
  context->frameRate = 1.0f / lastFrameTime;
  clock.Reset();

  while(context->window->App.GetEvent(event)) {

    // On Window close
    if(event.Type == sf::Event::Closed) {
      context->gameState = State_Closed;
      context->window->App.Close();
      break;
    }

  }
}
