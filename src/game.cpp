#include "game.hpp"

Game* Game::instance = NULL;  
  
Game* Game::Instance() {
  if (!instance) {
    instance = Game::Create();
  }
  return instance;
}

Game* Game::Create() {
  Game* g = new Game;

  Context::Init();
  g->win     = new Window();
  g->context = new Context(g->win);
  g->gui     = new GUIPage(g->win, g->context);
  
  g->context->gui = g->gui;
  
  return g;
}

void Game::Loop() {  
  while(context->gameState == State_InMenu) {
    context->HandleInput();
    context->Render();
  }
}
