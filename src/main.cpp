#include <iostream>

#include "context.hpp"

int main() {
  Context::Init();
  Window* win = new Window();
  GUIPage page(win);

  Context context(win);
  context.gui = page;


  GUIButton *but = new GUIButton("THIS BE TEXT");
  but->colFocused = sf::Color(255, 255, 255, 128);
  but->colUnfocused = sf::Color(1.0f, 1.0f, 1.0f, 0.5f);

  but->focused = true;

  sf::Shape rect = sf::Shape::Rectangle(200, 200, 600, 600, sf::Color::White);
  but->SetDimensions(400, 400);

  but->shape = rect;
  page.AddElement(but);
  
  win->Clear();

  page.Render();
  win->Render();

  page.Click(15, 60);

  std::cin.get();

  return 0;
}
