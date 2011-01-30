#ifndef _GUI_H_
#define _GUI_H_

#include "window.hpp"

class GUIElement;

struct GUIPage {
  Window *window;
  std::vector<GUIElement*> elements;
  GUIElement* focusedElement;

  GUIPage() {}
  GUIPage(Window* w);

  void AddElement(GUIElement* e);

  void Click(int x, int y);
  void Key(char key);

  void Render();

  bool DisplayDialog(std::string title, std::string prompt);
  std::string InputDialog(std::string title, std::string prompt);
};

struct GUIElement {
  GUIPage page;
  sf::Shape shape;
  bool focused;
  sf::Vector2<int> dimensions;

  sf::Color colFocused, colUnfocused;

public:
  void OnClick(int x, int y);
  void OnKey(char key);

  virtual void Render();

  void SetActive(bool val);
  void SetFocus(bool val);

  virtual void SetDimensions(int w, int h);

};

class GUIButton : public GUIElement {
  std::string label;
  sf::Color textColor;

public:
  GUIButton(std::string label) : label(label), textColor(sf::Color::Black) {
    dimensions.x = 0;
    dimensions.y = 0;
  }
                                 
  void SetText(std::string label);

  // overridden funcs
  void Render();

};

class GUITextField : GUIElement {
  std::string text;

public:
  void SetText(std::string text);
  void AppendText(std::string text);

};

#endif /* _GUI_H_ */
