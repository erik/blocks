#include "world.hpp"

WorldShape::WorldShape(float wi, float hi, sf::Color col) {
  w = wi;
  h = hi;
  color = col;  
}

// As a Box
WorldShape WorldShape::AsBox(b2Body* bod, float w, float h, bool isStatic) {
  WorldShape s(w, h);

  b2PolygonShape dynamicBox;

  dynamicBox.SetAsBox(w / 2, h / 2);
  
  b2FixtureDef fixtureDef;  
  fixtureDef.shape = &dynamicBox;
  fixtureDef.density = isStatic ? 0 : WorldConfig::density;
  fixtureDef.friction = WorldConfig::friction;
  
  bod->CreateFixture(&fixtureDef);
 
  s.isStatic = isStatic;
  s.body = bod;
  s.polygonShape = dynamicBox;

  return s;
}



float WorldShape::GetRotation() {
  float rads =  body->GetAngle();
  return -(rads * (180 / M_PI));
}

sf::Vector2<float> WorldShape::GetPosition() {
  b2Vec2 position = body->GetPosition();

  sf::Vector2<float> pos;
  pos.x = position.x * WorldConfig::scale; 
  pos.y = position.y * WorldConfig::scale; 

  return pos;
}

void WorldShape::SetRotation(float degrees) {
  float radians = degrees * (M_PI / 180);
  body->SetTransform(body->GetPosition(), -radians);
}

void WorldShape::SetColor(sf::Color c) {
  color = c;
}

// creates a proper rectangle which can be drawn to the screen
sf::Shape WorldShape::CreateRectangle() {
  sf::Shape s = sf::Shape::Rectangle(0, 0, w * WorldConfig::scale, h * WorldConfig::scale, color);
  s.SetCenter(w * WorldConfig::scale / 2, h * WorldConfig::scale / 2);
  s.SetRotation(GetRotation());
  s.SetPosition(GetPosition());
  return s;
}

void WorldShape::Destroy(World wo) {
  wo.GetWorld()->DestroyBody(body);
}
