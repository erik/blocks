#ifndef _WORLD_H_
#define _WORLD_H_

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <vector>

// Some configuration variables
namespace WorldConfig {
  const b2Vec2 gravity(0.0f, 9.8f);
  const float friction = 0.3f;
  const float density = 1.0f;
  const bool doSleep = true;
  const float timeStep = 1.0f / 60.0f;
  const float scale = 30.0f; // 30 pixels per meter
  const float width = 800.0f;
  const float height = 800.0f;
  const int velocityIterations = 8;
  const int positionIterations = 8;
}

class WorldShape;

class World {
  b2World* world;
  std::vector<WorldShape> shapes;

public:
  World();

  b2World* GetWorld();

  void Step();

  b2Body* CreateBody(b2BodyDef bodydef);
  void AddShape(WorldShape s);

  // these two return WorldShapes, automatically attaching them to the world
  WorldShape CreateBox(int x, int y, int width, int height, bool isStatic=false);
  WorldShape CreateCircle(int x, int y, int radius);
};

class WorldShape {
  float x, y, w, h;
  bool isStatic;
  sf::Color color;

  b2Body* body;
  b2PolygonShape polygonShape;
  b2FixtureDef fixtureDef;

public:
  WorldShape() {}
  WorldShape(float w, float h, sf::Color=sf::Color::White);

  void Destroy(World world);

  sf::Vector2<float> GetPosition();
  float GetRotation();
  float GetWidth();
  float GetHeight();

  void SetRotation(float degrees);
  void SetColor(sf::Color color);

  sf::Shape CreateRectangle();

  // This doesn't scale anything! That needs to be done manually, or by using
  // World::Create[Box, Circle]
  static WorldShape AsBox(b2Body* bod, float w, float h, bool isStatic);
  static WorldShape AsCircle(World* world, float x, float y, float r, bool isStatic);
};

#endif /* _WORLD_H_ */
