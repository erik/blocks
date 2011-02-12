#include "background.hpp"

// static members
sf::Image Background::skyImage;
sf::Image Background::cloudImage; 

void Background::Init() {  
  using namespace BackgroundConfig;

  std::string backName = imageDir + backgroundImageName;
  std::string cloudName = imageDir + cloudImageName;

  Background::skyImage.LoadFromFile(backName);
  Background::cloudImage.LoadFromFile(cloudName);
}

Background::Background(Context* con) {
  c = con;
  background.SetImage(skyImage);
  background.SetPosition(0, 0);
  // TODO: Scale sprite to background size
}

void Background::Step() {

  if(sf::Randomizer::Random(0, 500) == 1) {
    AddCloud();
  }

  for(int i = clouds.size() - 1; i >= 0 ; --i) {
    int curX = clouds[i].GetPosition().x;
    
    // erase clouds that have drifted off the screen
    if(curX >= 800 + 50) {
      clouds.erase(clouds.begin() + i);
    } else {
      clouds[i].SetX(curX + BackgroundConfig::xDrift);
    }
    
  }
}

void Background::Render() {
  c->window->Draw(background);
  for(unsigned int i = 0; i < clouds.size(); ++i) {
    c->window->Draw(clouds[i]);
  }
}


void Background::AddCloud() {
  sf::Sprite cloud;
  cloud.SetImage(cloudImage);

  // create clouds only in top 3 / 4 of screen
  int y = sf::Randomizer::Random(0, 800 - 800 / 4.0);
  cloud.SetPosition(0 - cloud.GetSize().x, y);

  clouds.push_back(cloud);

}
