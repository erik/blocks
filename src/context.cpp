#include "context.hpp"
#include "window.hpp"

void Context::HandleInput() {
  const sf::Input& Input = window->App.GetInput();

  switch(gameState) {
  case State_InMenu:
    gui->HandleInput(Input); 
    break;
  default:
    std::cerr << "Unrecognized game state" << std::endl;
  }

  sf::Event Event;
  while (window->App.GetEvent(Event))
    {

      if (Event.Type == sf::Event::Closed || ((Event.Type == sf::Event::KeyPressed) && 
                                              (Event.Key.Code == sf::Key::Escape))) {
        gameState = State_Closed;
        break;

      } else {

        switch(gameState) {

        case State_InMenu:
          gui->HandleEvent(Event);
          break;

        default:
          //this needs to be implementered
          std::cerr << "Unrecognized game state" << std::endl;
        }
      }
    }
}

void Context::Render() {
  window->Clear();

  // TODO: make this work on stuff other than the GUI
  
  gui->Render();
  window->Render();
}

void Context::Init() {
  Window::Init();
}
