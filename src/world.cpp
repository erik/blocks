#include <Box2D/Box2D.h>

#include "world.hpp"

void World::AddShape(WorldShape s) {
  shapes.push_back(s);
}

WorldShape World::CreateBox(int x, int y, int width, int height, bool isStatic) {
  const float scale(WorldConfig::scale);

  b2BodyDef bodyDef;
  bodyDef.position.Set(x / scale, y / scale);
  if(!isStatic) {
    bodyDef.type = b2_dynamicBody;
  }

  b2Body* body = world->CreateBody(&bodyDef);  

  WorldShape shape = WorldShape::AsBox(body, width / scale, width / scale, isStatic);

  AddShape(shape);
  return shape;
}


// As a Box
WorldShape WorldShape::AsBox(b2Body* bod, float w, float h, bool isStatic) {
  WorldShape s;

  b2PolygonShape dynamicBox;
  dynamicBox.SetAsBox(w, h);
  
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



