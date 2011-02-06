#ifndef _SCENE_H_
#define _SCENE_H_

#include "world.hpp"
#include "context.hpp"

class Context;

class Scene {
protected:
  World world;
  Context* context;

public:
  virtual void Init(Context *c, World world)=0;
  virtual void Step()=0;
  virtual void Render()=0;
};

class MenuScene : public Scene {
  WorldShape floor;
  std::vector<WorldShape> blocks;
  
public:
  void Init(Context* c, World world);
  void Step();
  void Render();
};


#endif /* _SCENE_H_ */
