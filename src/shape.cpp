#include <cmath>
#include "SFML/Graphics.hpp"

/*double angle2D(double x1, double y1, double x2, double y2)
{
   double dtheta,theta1,theta2;

   double twopi = M_PI * 2;

   theta1 = atan2(y1,x1);
   theta2 = atan2(y2,x2);
   dtheta = theta2 - theta1;
   while (dtheta > M_PI)
      dtheta -= twopi;
   while (dtheta < -M_PI)
      dtheta += twopi;

   return(dtheta);
} 

bool pointIntersectsShape(int x, int y, sf::Shape shape) {
  unsigned int numbVerts = shape.GetNbPoints();
  double angle = 0.0;
  for(unsigned int i = 0; i < numbVerts; ++i) {
    sf::Vector2f vec = shape.GetPointPosition(i);
    sf::Vector2f vec2 = shape.GetPointPosition((i + 1) % numbVerts);
    
    int x1, x2, y1, y2;

    x1 = vec.x  - x;
    x2 = vec2.x - x;
    y1 = vec.y  - y;
    y2 = vec2.y - y;

    angle += angle2D(x, y, x2, y2);

  }
  if(abs(angle) < M_PI) {
    return true;
  } 
  return false;
}*/


bool pointIntersectsShape(int x, int y, sf::Shape shape) {
  // TODO: Hardcoding this is pretty much the dumbest 
  // thing in the history of forever.

  sf::Vector2<float> ltop = shape.GetPointPosition(0);
  sf::Vector2<float> rbot = shape.GetPointPosition(2);

  sf::Rect<float>::Rect hitbox(ltop.x, ltop.y, rbot.x, rbot.y);

  return hitbox.Contains(x, y);

}
