#include "scene.hpp"
#include <SFML/Graphics.hpp>


void MenuScene::Init(Context *c) {
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

void MenuScene::HandleInput(const sf::Input& in) {
  context->gui->HandleInput(in);
}

void MenuScene::HandleEvent(sf::Event e) {
  context->gui->HandleEvent(e);
}



// Game Scene //

void GameScene::Init(Context* c) {
  context = c;

  platform = world.CreateBox(200, 700, 400, 10, true);
  platform.SetColor(sf::Color(0x44, 0x44, 0x44, 255));

  x = 800.0 / 2;

  GenerateShape();
}

void GameScene::Step() {
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


void GameScene::Render() {
  sf::Shape s;

  for(int i = 50 + h / 2, col = 0x66; i < 700; i += 10, col -= 2) {
    if (col <= 0) col = 0;
    s = sf::Shape::Line(x + w / 2, i, x + w / 2, i + 10, 3.0,
                        sf::Color(col, col, col, 128));
    context->window->Draw(s);
  }
  
  s = sf::Shape::Rectangle(0, 0, w, h, sf::Color(0x66, 0x66, 0x66, 255));
  s.SetCenter(w / 2, h / 2);
  s.SetPosition(x + w / 2, 50 + h / 2);
  s.SetRotation(rot);
  context->window->Draw(s);

  for(unsigned int i = 0; i < blocks.size(); ++i) {
    s = blocks[i].CreateRectangle();
    context->window->Draw(s);
  }
  
  s = platform.CreateRectangle();
  context->window->Draw(s);

}

void GameScene::HandleInput(const sf::Input& in) {
  context->gui->HandleInput(in);

  if(in.IsKeyDown(sf::Key::Left)) {
    x -= 4;
  }
  if(in.IsKeyDown(sf::Key::Right)) {
    x += 4;
  }
  if(in.IsKeyDown(sf::Key::Q)) {
    rot -= 1 % 360;
  }
  if(in.IsKeyDown(sf::Key::E)) {
    rot += 1 % 360;
  }
}

void GameScene::HandleEvent(sf::Event e) {
  context->gui->HandleEvent(e);

  if(e.Type == sf::Event::KeyReleased) {
    if(e.Key.Code == sf::Key::Space) {
      DropShape();
      GenerateShape();
    }
  } 
}

void GameScene::GenerateShape() {
  w = sf::Randomizer::Random(20, 50);
  h = sf::Randomizer::Random(20, 50);  
  rot = sf::Randomizer::Random(0, 360);
}

void GameScene::DropShape() {
  WorldShape ws = world.CreateBox(x, 50, w, h, false);
  int r = sf::Randomizer::Random(1, 256);
  int g = sf::Randomizer::Random(1, 256);
  int b = sf::Randomizer::Random(1, 256);
  ws.SetColor(sf::Color(r, g, b, 255));
  ws.SetRotation(rot);
  
  blocks.push_back(ws);
}
