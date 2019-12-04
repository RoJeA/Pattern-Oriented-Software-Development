#ifndef TRIANGULAR_PYRAMID_H
#define TRIANGULAR_PYRAMID_H

#include<math.h>
#include "solid.h"
class TriangularPyramid
{
public:
  TriangularPyramid(double x1, double y1, double x2, double y2, double x3, double y3, double height):_x1(x1),_y1(y1),_x2(x2),_y2(y2),_x3(x3),_y3(y3),_height(height){
    a=sqrt(pow(_x1-_x2,2)+pow(_y1-_y2,2));
    b=sqrt(pow(_x2-_x3,2)+pow(_y2-_y3,2));
    c=sqrt(pow(_x3-_x1,2)+pow(_y3-_y1,2));
    s=(a+b+c)/2;
  };
  double bottomArea() const{
    return sqrt(s*(s-a)*(s-b)*(s-c));
  } ;
  double volume() const{
    return bottomArea()*_height/3;
  };
private:
  double _x1;
  double _y1;
  double _x2;
  double _y2;
  double _x3;
  double _y3;
  double _height;
  double a,b,c;
  double s;
};
#endif
