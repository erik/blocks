#include "input.hpp"

const sf::Input& InputHandler::HandleInput() {
  const sf::Input& input = context->window->App.GetInput();
  sf::Event event;
  
  mouse.x = input.GetMouseX();
  mouse.y = input.GetMouseY();

  lastFrameTime = clock.GetElapsedTime();
  context->frameRate = 1.0 / lastFrameTime;
  clock.Reset();

  while(context->window->App.GetEvent(event)) {

    // On Window close
    if(event.Type == sf::Event::Closed || ((event.Type == sf::Event::KeyPressed) && 
                                              (event.Key.Code == sf::Key::Escape))) {
      context->gameState = State_Closed;
      context->window->App.Close();
      break;
    } else {
     context->scene->HandleEvent(event);
    }

  }

  return input;

}
