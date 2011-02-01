#include "window.hpp"

sf::VideoMode Window::DefaultVideoMode;

Window::Window(std::string title) {
  fullscreen =false;
  windowTitle = title;
  videoMode = Window::DefaultVideoMode;

  App.SetFramerateLimit(60);
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

Window::~Window() {
  App.Close();
}

void Window::Init() {
  Window::DefaultVideoMode  = sf::VideoMode(800, 800, 32);
}

void Window::Render() {
  App.Display();
}

void Window::Clear() {
  App.Clear();
}

void Window::Draw(sf::Drawable& obj) {
  App.Draw(obj);
}
