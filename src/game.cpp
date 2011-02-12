#include "game.hpp"
#include "world.hpp"

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
  g->context->scene   = new MenuScene();
  g->context->game    = g;
  g->context->input   = new InputHandler(g->context);

  g->context->gui = g->gui;

  g->context->background = new Background(g->context);

  g->CreateMenu();

  return g;
}

void Game::Loop() {
  while(context->gameState != State_Closed) {   
    context->Step();
    context->HandleInput();
    context->Render();
  }
}

static void exitOnClick(GUIElement* const e, int x, int y) {
  std::cout << "Goodbye, cruel world!" << std::endl;
  e->page.context->gameState = State_Closed;
}

static void startGameOnClick(GUIElement* const e, int x, int y) {
  Game *g = e->page.context->game;

  g->context->gameState = State_InGame;
  g->context->gui = new GUIPage(g->win, g->context);
  g->context->scene= new GameScene();

  g->CreateGame();
}


void Game::CreateMenu() {

  // Create the scene

  context->scene->Init(context);
  
  // Create the GUI

  sf::Color invis(0, 0, 0, 0);
  sf::Color gray(0x22, 0x22, 0x22, 128);
  
  sf::Rect<int> rect(200, 200, 600, 250);
  sf::Rect<int> rect2(200, 275, 600, 325);
  sf::Rect<int> rect3(200, 350, 600, 400); 

  GUIButton *but =  new GUIButton("START GAME", rect, gray, invis);
  GUIButton *but2 = new GUIButton("OPTIONS",    rect2, gray, invis);
  GUIButton *but3 = new GUIButton("EXIT",       rect3, gray, invis);

  but3->SetOnClick(exitOnClick);
  but->SetOnClick(startGameOnClick);

  but->SetFontSize(20.0f);
  but2->SetFontSize(20.0f);
  but3->SetFontSize(20.0f);

  gui->AddElement(but);
  gui->AddElement(but2);
  gui->AddElement(but3);
}

void Game::CreateGame() {
  // Create the scene
  
  context->scene->Init(context);
  
  // Create the GUI
  
  sf::Color gray(0x44, 0x44, 0x44, 128);

  sf::Rect<int> scoreRect(100, 100, 200, 150);

  GUIButton *scoreBut = new GUIButton("SCORE: ", scoreRect, gray, gray);

  gui->AddElement(scoreBut);

}
