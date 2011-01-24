#include "window.hpp"

sf::VideoMode Window::DefaultVideoMode;

Window::Window(std::string title) {
  fullscreen =false;
  windowTitle = title;
  videoMode = Window::DefaultVideoMode;

  App.Create(videoMode, windowTitle.c_str());
}

Window::Window(sf::VideoMode mode) {
  fullscreen = false;
  windowTitle = "Blocks";
  videoMode = mode;

  App.Create(videoMode, windowTitle.c_str());
}

Window::Window(int width, int height, int bpp) {
  fullscreen = false;
  windowTitle = "Blocks";
  
  videoMode = sf::VideoMode(width, height, bpp);
  
  App.Create(videoMode, windowTitle.c_str());
}

void Window::Init() {
  Window::DefaultVideoMode  = sf::VideoMode(800, 800, 32);
}
