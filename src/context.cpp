#include "context.hpp"
#include "window.hpp"
#include "scene.hpp"

void Context::HandleInput() {
  const sf::Input& Input = input->HandleInput();

  scene->HandleInput(Input); 
}

void Context::Render() {
  window->Clear();
  background->Render();

  RenderState();

  window->Render();
}

void Context::Init() {
  Window::Init();
  Background::Init();
}

void Context::RenderState() {
  switch(gameState) {
  case State_InMenu:
    scene->Step();
    scene->Render();
    gui->Render();
    break;
  case State_InGame:
    scene->Step();
  case State_Paused:
    scene->Render();
    gui->Render();
    break;
  case State_Closed:
    break;
  default:
    std::cerr << "Todo: implement me. Context::RenderState()" << std::endl;
  }
}

void Context::Step() {
  background->Step();
}
