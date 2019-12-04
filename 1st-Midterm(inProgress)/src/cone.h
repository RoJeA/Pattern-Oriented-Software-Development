#ifndef CONE_H
#define  CONE_H

#include "solid.h"
#include <math.h>
using namespace std;
class Cone:public Solid
{
public:
  Cone(double x1,double y1,double x2,double y2, double height):_x1(x1),_y1(y1),_x2(x2),_y2(y2),_height(height){
    radius = sqrt(pow(_x1-_x2,2) + pow(_y1-_y2,2));
    if(radius==0){
      throw string("Bottom is not a Circle!");
    }
  }
  double bottomArea() const{
    // double radius = sqrt(pow(_x1-_x2,2) + pow(_y1-_y2,2));
    return pow(radius,2) * M_PI;
  };
  double volume() const{
    return bottomArea()* _height /3;
  };
private:
  double _x1;
  double _y1;
  double _x2;
  double _y2;
  double _height;
  double radius;
};

#endif
