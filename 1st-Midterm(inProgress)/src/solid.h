#ifndef SOLID_H
#define SOLID_H

class Solid {
public:
  virtual double bottomArea() const = 0;
  virtual double volume() const = 0;

  virtual void add(Solid* s){};
  virtual int numberOfChild(){
    return nullptr;
  };
};
#endif
