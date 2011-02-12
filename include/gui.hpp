#ifndef _GUI_H_
#define _GUI_H_

#include "window.hpp"
#include "context.hpp"

class GUIElement;
struct Context;

// GUIPage //

struct GUIPage {
  Window *window;
  Context *context;
  std::vector<GUIElement*> elements;
  GUIElement* focusedElement;

  GUIPage() {}
  GUIPage(Window* w, Context* c=NULL);

  void AddElement(GUIElement* e);

  void HandleInput(const sf::Input& input);
  void HandleEvent(sf::Event event);

  void Click(int x, int y);
  void Key(char key);

  void Render();

  bool DisplayDialog(std::string title, std::string prompt);
  std::string InputDialog(std::string title, std::string prompt);
};

// GUIElement //

typedef void (*OnClickCallback)(GUIElement* const, int, int);
typedef void (*OnKeyCallback)(GUIElement* const, char key);

// TODO: Allow setting outline color + width

struct GUIElement {
  GUIPage page;
  sf::Rect<int>::Rect shape;
  bool focused;
  sf::Color colFocused, colUnfocused;
  sf::Font font;
  float fontSize;

  OnClickCallback onClick;
  OnKeyCallback onKey;

public:
  GUIElement() {
    onClick = NULL;
    onKey = NULL;
    font = sf::Font::GetDefaultFont();
    fontSize = 30;
  }

  void SetFont(sf::Font font);
  void SetFontSize(float size);

  virtual void SetOnClick(OnClickCallback callback) {
    onClick = callback;
  }
  virtual void SetOnKey(OnKeyCallback callback) {
    onKey = callback;
  }

  virtual void OnClick(int x, int y);
  virtual void OnKey(char key);

  virtual void SetFocus(bool val);

  virtual void Render();
};

// GUIButton //

class GUIButton : public GUIElement {
  std::string label;
  sf::Color textColor;

public:
  GUIButton(std::string label, sf::Rect<int>::Rect s, sf::Color foc, sf::Color unFoc) : 
    label(label), textColor(sf::Color::Black) {

    GUIElement::GUIElement();

    shape = s;

    colFocused = foc;
    colUnfocused = unFoc;
  }
                                 
  void SetText(std::string label);

  // overridden funcs
  void Render();
  void OnClick(int x, int y);
  void OnKey(char key);
};

class GUITextField : GUIElement {
  std::string text;

public:
  void SetText(std::string text);
  void AppendText(std::string text);

};

#endif /* _GUI_H_ */
