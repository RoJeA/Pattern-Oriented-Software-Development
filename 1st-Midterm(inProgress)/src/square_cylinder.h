#ifndef SQUARECYLINDER_H
#define SQUARECYLINDER_H

#include<math.h>
#include "solid.h"
class SquareCylinder
{
public:
  SquareCylinder(double edge, double height):_edge(edge),_height(height){};
  double bottomArea() const{
    return pow(_edge,2);
  };
  double volume() const{
    return bottomArea()*_height;
  };
private:
  double _edge;
  double _height;
};
#endif
