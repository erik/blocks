#include "scene.hpp"
#include <SFML/Graphics.hpp>


#include <sstream>

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


/*YO, ADD COMBOS, SUBTRACT SCORE EACH TIME SOMETHING FALLS OFF,
POINTS DEPEND ON HEIGHT */
/* ALSO, LOTS OF HACKED STUFF IN HERE */

void GameScene::Render() {
  sf::Shape s;


  // Draw the alignment line
  for(int i = 50 + h / 2, col = 0x66; i < 700; i += 10, col -= 4) {
    if (col <= 0) col = 0;
    s = sf::Shape::Line(x + w / 2, i, x + w / 2, i + 10, 1.0,
                        sf::Color(col, col, col, 128));
    context->window->Draw(s);
    // To make a dashed line
    i += 10;
  }
  
  // Draw the held shape
  s = sf::Shape::Rectangle(0, 0, w, h, sf::Color(0x66, 0x66, 0x66, 255));
  s.SetCenter(w / 2, h / 2);
  s.SetPosition(x + w / 2, 50 + h / 2);
  s.SetRotation(rot);
  context->window->Draw(s); 


  // Draw the blocks
  for(unsigned int i = 0; i < blocks.size(); ++i) {
    s = blocks[i].CreateRectangle();
    context->window->Draw(s);
  }

  int highestIndex = -1;
  float highestPoint = -1;

  // Draw the lines and heights
  for(unsigned int i = 0; i < blocks.size(); ++i) {
    sf::Vector2<float> pos = blocks[i].GetPosition();
    float w = blocks[i].GetWidth();
    float h = blocks[i].GetHeight();

    float midWidth = pos.x + w / 2;
    float midHeight = pos.y + h / 2;

    int mapped = 256 - map(pos.y, 0, 700, 0, 256);

    if((pos.y < highestPoint || highestIndex == -1)) {
      highestPoint = pos.y;
      highestIndex = i;
    }

    sf::Color color = (700 - pos.y) <= 0 ? 
      sf::Color::Red : sf::Color(255, 256 - mapped, 256 - mapped, mapped);

    if(pos.y <= 700 - 50 || pos.y >= 700 - 0) {
      s = sf::Shape::Line(midWidth, midHeight, midWidth + 50, midHeight, 1.0, color);
      
      context->window->Draw(s);
      
      std::ostringstream buff;
      buff << 700 - pos.y;
      
      sf::String str = sf::String(buff.str(), sf::Font::GetDefaultFont(), 15.0);
      
      str.SetPosition(midWidth + 50, midHeight - str.GetSize() / 2);
      str.SetColor(color);
      
      context->window->Draw(str);
    }
  }

  // Draw the bracket
  if(blocks.size() > 1 && highestIndex != -1) {
    s = sf::Shape::Line(700.0 / 2 - 100, 700, 100, 700, 1.0, sf::Color::Red);
    context->window->Draw(s);
    s = sf::Shape::Line(700.0 / 2 - 100, highestPoint, 100, highestPoint, 1.0, sf::Color::Red);
    context->window->Draw(s);
    s = sf::Shape::Line(100, 700, 100, highestPoint, 1.0, sf::Color::Red);
    context->window->Draw(s);
  }


  s = platform.CreateRectangle();
  context->window->Draw(s);

}

void GameScene::HandleInput(const sf::Input& in) {
  context->gui->HandleInput(in);

  if(in.IsKeyDown(sf::Key::Left)) {
    x -= x ? 4 : 0;
  }
  if(in.IsKeyDown(sf::Key::Right)) {
    x += x >= 800 ? 0 : 4;;
  }
  if(in.IsKeyDown(sf::Key::Q)) {
    rot -= 2 % 360;
  }
  if(in.IsKeyDown(sf::Key::E)) {
    rot += 2 % 360;
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
