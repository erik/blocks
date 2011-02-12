#ifndef _SCENE_H_
#define _SCENE_H_

#include "world.hpp"
#include "context.hpp"
#include "gui.hpp"

class Context;
class GUIPage;
class GUIButton;

class Scene {
protected:
  World world;
  Context* context;

public:
  Scene() {};

  virtual void Init(Context *c)=0;
  virtual void Step()=0;
  virtual void Render()=0;

  virtual void HandleInput(const sf::Input& in)=0;
  virtual void HandleEvent(sf::Event e)=0;
};

class MenuScene : public Scene {
  WorldShape floor;
  std::vector<WorldShape> blocks;
  
public:
  void Init(Context* c);
  void Step();
  void Render();

  void HandleInput(const sf::Input& in);
  void HandleEvent(sf::Event e);
};

class GameScene : public Scene {
  WorldShape platform;
  std::vector<WorldShape> blocks;

  float x, w, h, rot;
  bool holdingShape;

  GUIPage *gui;
  GUIButton *scoreBut;
  GUIButton *timeBut;

  int droppedBlocks;
  float score;

  sf::Clock clock;
  float startTime;

public:
  void Init(Context *c);
  void Step();
  void Render();

  void HandleInput(const sf::Input& in);
  void HandleEvent(sf::Event e);

private:
  void GenerateShape();
  void DropShape();
};


#endif /* _SCENE_H_ */
