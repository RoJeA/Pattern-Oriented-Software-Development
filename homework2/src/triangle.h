#ifndef TRIANGLE_H
#define TRIANGLE_H

#include"shape.h"
#include<math.h>
#include <sstream>
using namespace std;
class Triangle:public Shape
{
public:
  Triangle(double x1, double y1, double x2, double y2, double x3, double y3): _x1(x1), _x2(x2), _x3(x3), _y1(y1), _y2(y2), _y3(y3)
  {
    l1 = sqrt(pow((_x1-_x2),2) + pow((_y1-_y2),2)); // sqrt(a1^2+b1^2)
    l2 = sqrt(pow((_x2-_x3),2) + pow((_y2-_y3),2)); // sqrt(a2^2+b2^2)
    l3 = sqrt(pow((_x3-_x1),2) + pow((_y3-_y1),2)); // sqrt(a3^2+b3^2)

    if(isIsoscelesTriangle()==false)
    {
      throw string("Not a IsoscelesTriangle.");
      //This statement will not be executed.
    }
  }
  // give you three points (x1,y1), (x2,y2), (x3,y3) to calculate area and perimeter
  double area() const
  {
    return abs((_x1*(_y2-_y3))+(_x2*(_y3-_y1))+(_x3*(_y1-_y2)))/2.0;
    //area	=	abs(Ax ( By	− Cy ) + Bx ( Cy − Ay )	+ Cx ( Ay − By ))/2
  }
  double perimeter() const
  {
    return l1+l2+l3;
    //AB^2 = dx^2 + dy^2
  }
  bool isIsoscelesTriangle()
  {
    if((_x1==_x2&&_x2==_x3)||(_y1==_y2&&_y2==_y3))
    {
      return false;
    }
    //**兩邊和大於第三邊
    else if(l1==l2 || l2==l3 || l3==l1)
    {
      return true;
    }
    else
    {
      return false;
    }
  }
  double sumOfSquares() const
  {
    return pow(area(),2) + pow(perimeter(),2);
  }
private:
  double _x1;
  double _x2;
  double _x3;
  double _y1;
  double _y2;
  double _y3;
  double l1,l2,l3;//邊長
};
#endif
