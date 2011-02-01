#include <iostream>

#include "context.hpp"

int main() {
  Context::Init();
  Window* win = new Window();
  GUIPage page(win);

  sf::Color lightgreen(0, 255, 0, 200);
  sf::Color green(0, 255, 0, 128);

  sf::Shape rect = sf::Shape::Rectangle(100, 100, 400, 200, sf::Color::White);
  sf::Shape rect2 = sf::Shape::Rectangle(100, 250, 400, 350, sf::Color::White);
  sf::Shape rect3 = sf::Shape::Rectangle(100, 400, 400, 500, sf::Color::White);

  GUIButton *but =  new GUIButton("THIS BE TEXT", rect, 300, 100, green, lightgreen);
  GUIButton *but2 = new GUIButton("OTHER TEXT",  rect2, 300, 100, green, lightgreen);
  GUIButton *but3 = new GUIButton("MORE TEXT",   rect3, 300, 100, green, lightgreen);

  page.AddElement(but);
  page.AddElement(but2);
  page.AddElement(but3);

  Context context(win);
  context.gui = page;
  context.window->App.SetFramerateLimit(60);
  
  while(context.gameState == State_InMenu) {
    context.HandleInput();
    context.Render();
  }

  return 0;
}
