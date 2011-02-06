#include "scene.hpp"

void MenuScene::Init(Context *c, World w) {
  world = w;
  context = c;

  floor = world.CreateBox(200, 700, 400, 10, true);
  floor.SetColor(sf::Color(0x44, 0x44, 0x44, 255));

}

void MenuScene::Step() {
  
  if(sf::Randomizer::Random(1, 20) == 5) {
    int w = sf::Randomizer::Random(1, 50);
    int h = sf::Randomizer::Random(1, 50); 
    int x = sf::Randomizer::Random(1, 800);

    int r = sf::Randomizer::Random(50, 256);
    int g = sf::Randomizer::Random(50, 256);
    int b = sf::Randomizer::Random(50, 256);

    WorldShape ws = world.CreateBox(x, -50, w, h, false);
    ws.SetColor(sf::Color(r, g, b, 255));
    
    blocks.push_back(ws);
  }

  // remove blocks that are off screen
  std::vector<WorldShape>::iterator iter = blocks.begin();
  while(iter != blocks.end()) {
    if(iter->GetPosition().y >= 800) {
      iter->Destroy(world);
      iter = blocks.erase(iter);
    } else {
      ++iter;
    }
  }
    
  world.Step();

}

void MenuScene::Render() {
  sf::Shape s;

  for(unsigned int i = 0; i < blocks.size(); ++i) {
    s = blocks[i].CreateRectangle();
    context->window->Draw(s);
  }

  s = floor.CreateRectangle();
  context->window->Draw(s);
}
