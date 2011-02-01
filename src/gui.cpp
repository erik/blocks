#include "gui.hpp"
#include "blocks.hpp"
#include <iostream>

// GUIPage //

GUIPage::GUIPage(Window* w, Context* c) {
  window = w;
  context = c;
  focusedElement = NULL;
}

void GUIPage::AddElement(GUIElement* e) {
  e->page = *this;
  elements.push_back(e);
}

void GUIPage::HandleInput(const sf::Input& input) {
  int x = input.GetMouseX();
  int y = input.GetMouseY();

  focusedElement = NULL;

  // TODO: This loop is also repeated in GUIPage::Click().
  // bring it out into a separate method.
  for(unsigned int i = 0; i < elements.size(); ++i) {
    if(elements[i]->shape.Contains(x, y)) {
      elements[i]->focused = true;

      focusedElement = elements[i];
      break;
    } else {
      elements[i]->focused = false;
    }
  }
  
}

void GUIPage::HandleEvent(sf::Event event) {
  // make sure there is actually an element
  if(focusedElement) {
    if(event.Type == sf::Event::MouseButtonReleased) {
      focusedElement->OnClick(event.MouseButton.X, event.MouseButton.Y);
    }
  }
}

void GUIPage::Render() {
  std::vector<GUIElement*>::iterator iter;
  for(iter = elements.begin(); iter < elements.end(); iter++) {
    (*iter)->Render();
  }
}

void GUIPage::Click(int x, int y) {
  for(unsigned int i = 0; i < elements.size(); ++i) {
    if(elements[i]->shape.Contains(x, y)) {
      std::cout << "Click hit element: " << i << std::endl;
      break;
    }
  }
}


// GUIElement //

// stub
void GUIElement::Render() {
  sf::Color col;
  
  if(focused) {
    col = colFocused;
  } else {
    col = colUnfocused;
  }
    
  sf::Shape drawRect = sf::Shape::Rectangle(shape.Left, shape.Top, shape.Right, shape.Bottom, col);
    
  page.window->Draw(drawRect);
}

// stub
void GUIElement::OnClick(int x, int y) {
  // if a callback exists, call that instead
  if(onClick != NULL) {
    return onClick(this, x, y);
  }
  std::cout << "You clicked me!";
}

void GUIElement::OnKey(char x) {
  if(onKey != NULL) {
    return onKey(this, x);
  }
  std::cout << "You hit me with: " << x ;
}

void GUIElement::SetFocus(bool val) {
  if(val) {
    page.focusedElement = this;
  } else {
    if(focused) {
      page.focusedElement = NULL;
    }
  }
  focused = val;
}

// GUIButton //
void GUIButton::Render() {
  GUIElement::Render();

  // TODO: String color

  sf::String str = sf::String(label.c_str());
  str.SetSize(30);

  // unmaintainable mess
  str.SetPosition(shape.Left + shape.GetWidth() / 2 - 
                  str.GetRect().GetWidth() / 2, shape.Top
                  + shape.GetHeight() / 2 - str.GetSize() / 2);

  page.window->Draw(str);
}

void GUIButton::OnClick(int x, int y) {
  GUIElement::OnClick(x, y);
  std::cout << " (Button: \"" << label << "\")" << std::endl;
}

void GUIButton::OnKey(char key) {
  GUIButton::OnKey(key);
  std::cout << " (Button: \"" << label << "\")" << std::endl;
}
