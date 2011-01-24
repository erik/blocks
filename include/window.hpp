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

  void setFullscreen(bool val);
  void setTitle(std::string title);

} ;

#endif /* _WINDOW_H_ */
