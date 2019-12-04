#ifndef COMPLEXSOLID_H
#define COMPLEXSOLID_H

#include<math.h>
#include <sstream>
#include<vector>
#include<algorithm>
#include "solid.h"

using namespace std;
class ComplexSolids:public Solid
{
public:
  ComplexSolids(std::vector<Solid*> * solids): _s(solids){};
  double bottomArea() const{
    double total = 0;
    for(vector<Solid*>::iterator it=_s->begin();it!=_s->end();it++){
      total +=(*it)->bottomArea();
    }
    return total;
  };
  double volume() const{
    double total = 0;
    for(vector<Solid*>::iterator it=_s->begin();it!=_s->end();it++){
      total += (*it)->volume();
    }
    return total;
  };
  void add(Solid* s) {
    _s->push_back(s);
  }
  int numberOfChild(){
    int numOfCh=0;
    for(vector<Solid*>::iterator it=_s->begin();it!=_s->end();it++){
      numOfCh+=1;
    }
    return numOfCh;
  }

private:
  vector<Solid*> * _s;
};

#endif
