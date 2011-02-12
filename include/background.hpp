#ifndef _BACKGROUND_H_
#define _BACKGROUND_H_

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

#include "context.hpp"

namespace BackgroundConfig {
  const std::string imageDir = "data/images/";
  const std::string backgroundImageName = "sky.tga";
  const std::string cloudImageName = "cloud.tga";

  const int xDrift = 1;
}

struct Context;

class Background {
  static sf::Image skyImage;
  static sf::Image cloudImage;

  Context* c;
  std::vector<sf::Sprite> clouds;
  sf::Sprite background;
  
public:
  static void Init();

  Background(Context* c);

  void Step();
  void Render();

  void AddCloud();
};

#endif /* _BACKGROUND_H_ */
