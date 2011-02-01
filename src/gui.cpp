#include "gui.hpp"
#include "blocks.hpp"
#include <iostream>

// GUIPage //

GUIPage::GUIPage(Window* w) {
  window = w;
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
    if(pointIntersectsShape(x, y, elements[i]->shape)) {
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
    if(pointIntersectsShape(x, y, elements[i]->shape)) {
      std::cout << "Click hit element: " << i << std::endl;
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
  
  shape.SetColor(col);
    
  page.window->Draw(shape);
}

// stub
void GUIElement::OnClick(int x, int y) {
  std::cout << "You clicked me!";
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


void GUIElement::SetDimensions(int x, int y) {
  dimensions.x = x;
  dimensions.y = y;
}

// GUIButton //
void GUIButton::Render() {
  GUIElement::Render();

  // TODO: String color

  sf::String str = sf::String(label.c_str());
  str.SetSize(30);

  // unmaintainable mess
  str.SetPosition(shape.GetPointPosition(0).x + dimensions.x / 2 - 
                  str.GetRect().GetWidth() / 2, shape.GetPointPosition(0).y
                  + dimensions.y / 2 - str.GetSize() / 2);

  page.window->Draw(str);
}

void GUIButton::OnClick(int x, int y) {
  GUIElement::OnClick(x, y);
  std::cout << " (Button: \"" << label << "\")" << std::endl;
}
