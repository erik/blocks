#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "world.hpp"

void World::Step() {
  world->Step(WorldConfig::timeStep, WorldConfig::velocityIterations, WorldConfig::positionIterations);
  world->ClearForces();
}

b2Body* World::CreateBody(b2BodyDef bodyDef) {
  return world->CreateBody(&bodyDef);
}

void World::AddShape(WorldShape s) {
  shapes.push_back(s);
}

WorldShape World::CreateBox(int x, int y, int width, int height, bool isStatic) {
  const float scale(WorldConfig::scale);

  b2BodyDef bodyDef;
  bodyDef.bullet = true;
  bodyDef.position.Set((x + width / 2) / scale, (y + height / 2) / scale);
  if(!isStatic) {
    bodyDef.type = b2_dynamicBody;
  }

  b2Body* body = CreateBody(bodyDef);

  WorldShape shape = WorldShape::AsBox(body, width / scale, height / scale, isStatic);

  AddShape(shape);
  return shape;
}


// WorldShape //

// As a Box
WorldShape WorldShape::AsBox(b2Body* bod, float w, float h, bool isStatic) {
  WorldShape s;
  s.w = w;
  s.h = h;

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

// creates a proper rectangle which can be drawn to the screen
sf::Shape WorldShape::CreateRectangle(sf::Color color) {
  sf::Shape s = sf::Shape::Rectangle(0, 0, w * WorldConfig::scale, h * WorldConfig::scale, color);
  s.SetCenter(w * WorldConfig::scale / 2, h * WorldConfig::scale / 2);
  s.SetRotation(GetRotation());
  s.SetPosition(GetPosition());
  return s;
}
