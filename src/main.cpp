#include <iostream>

#include "context.hpp"

void exitOnClick(GUIElement* const e, int x, int y) {
  std::cout << "Goodbye, cruel world!" << std::endl;
  e->page.context->gameState = State_Closed;
}

int main() {
  Context::Init();
  Window* win = new Window();
  Context context(win);
  context.window->App.SetFramerateLimit(60);

  GUIPage page(win, &context);
  context.gui = &page;

  sf::Color lightgreen(0, 255, 0, 200);
  sf::Color green(0, 255, 0, 128);

  sf::Rect<int>::Rect rect(100, 100, 400, 200);
  sf::Rect<int>::Rect rect2(100, 250, 400, 350);
  sf::Rect<int>::Rect rect3(100, 400, 400, 500);

  GUIButton *but =  new GUIButton("THIS BE TEXT", rect, green, lightgreen);
  GUIButton *but2 = new GUIButton("OTHER TEXT",  rect2, green, lightgreen);
  GUIButton *but3 = new GUIButton("EXIT",        rect3, green, lightgreen);
  but3->SetOnClick(exitOnClick);

  page.AddElement(but);
  page.AddElement(but2);
  page.AddElement(but3);
  
  while(context.gameState == State_InMenu) {
    context.HandleInput();
    context.Render();
  }

  return 0;
}
