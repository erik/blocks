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
  
  g->context->gui = g->gui;
  
  g->CreateMenuGUI();

  return g;
}

void Game::Loop() {
  World w;
  WorldShape floor = w.CreateBox(250, 700, 200, 10, true);

  std::vector<WorldShape> shapes;

  while(context->gameState == State_InMenu) {
    int x = sf::Randomizer::Random(0, 800);
    int w_ = sf::Randomizer::Random(1, 50);
    int h = sf::Randomizer::Random(1, 50);

    if(sf::Randomizer::Random(1, 20) == 5)
      shapes.push_back(w.CreateBox(x, 0, w_, h, false));

    w.Step();
    
    context->HandleInput();
    // context->Render();

    context->window->Clear();

    sf::Shape s;
    
    for(unsigned int i = 0; i < shapes.size(); ++i) {
      s = shapes[i].CreateRectangle();
      context->window->Draw(s);
    }

    s = floor.CreateRectangle(sf::Color::Green);
    context->window->Draw(s);

    context->window->Render();

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
