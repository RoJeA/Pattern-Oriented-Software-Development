#ifndef ELLIPSE_H
#define ELLIPSE_H

#include"shape.h"
#include<math.h>
#include <sstream>
using namespace std;
class Ellipse: public Shape
{
public:
  Ellipse(double a, double b):_a(a), _b(b)
  {

  }

  double area() const
  {
    return M_PI * _a * _b;
  }

  double perimeter() const
  {
    return 2 * M_PI * _b + 4 * ( _a - _b );
  }

  string getDetails() const {
    stringstream ss;
    ss << "ellipse" << " " << _a << " " << _b;
    return ss.str();
  }
private:
  double _a;
  double _b;
};
#endif
