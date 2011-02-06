#include <Box2D/Box2D.h>

#include <iostream>
#include "world.hpp"

World::World() {
  world = new b2World(WorldConfig::gravity, WorldConfig::doSleep);
}

b2World* World::GetWorld() {
  return world;
}

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
  bodyDef.position.Set((x + width / 2) / scale, (y + height / 2) / scale);

  if(!isStatic) {
    bodyDef.type = b2_dynamicBody;
  } else {
    // protect against tunneling with static objects
    bodyDef.bullet = true;
  }

  b2Body* body = CreateBody(bodyDef);

  WorldShape shape = WorldShape::AsBox(body, width / scale, height / scale, isStatic);

  AddShape(shape);
  return shape;
}
