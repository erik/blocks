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
  
  g->CreateMenuGUI();

  return g;
}

void Game::Loop() {  
  while(context->gameState == State_InMenu) {
    context->HandleInput();
    context->Render();
  }
}

static void exitOnClick(GUIElement* const e, int x, int y) {
  std::cout << "Goodbye, cruel world!" << std::endl;
  e->page.context->gameState = State_Closed;
}


void Game::CreateMenuGUI() {

  sf::Color lightgreen(0, 255, 0, 200);
  sf::Color green(0, 255, 0, 128);
  
  sf::Rect<int>::Rect rect(100, 100, 400, 200);
  sf::Rect<int>::Rect rect2(100, 250, 400, 350);
  sf::Rect<int>::Rect rect3(100, 400, 400, 500);
  
  GUIButton *but =  new GUIButton("THIS BE TEXT", rect, green, lightgreen);
  GUIButton *but2 = new GUIButton("OTHER TEXT",  rect2, green, lightgreen);
  GUIButton *but3 = new GUIButton("EXIT",        rect3, green, lightgreen);
  but3->SetOnClick(exitOnClick);

  gui->AddElement(but);
  gui->AddElement(but2);
  gui->AddElement(but3);  
}
