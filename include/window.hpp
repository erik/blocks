#ifndef _WINDOW_H_
#define _WINDOW_H_

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

struct Window {
  sf::RenderWindow    App;
  bool                fullscreen;
  bool                open;
  std::string         windowTitle;
  sf::VideoMode       videoMode;
  static sf::VideoMode DefaultVideoMode;

  static void Init();

  Window(std::string title="Blocks");
  Window(sf::VideoMode vm);
  Window(int width, int height, 
         int bpp = 32);

  ~Window();

  void setFullscreen(bool val);
  void setTitle(std::string title);
  void Render();
  void Clear();
  void Draw(sf::Drawable& obj);

} ;

#endif /* _WINDOW_H_ */
