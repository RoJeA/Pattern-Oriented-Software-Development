#ifndef ELEMENT_H
#define ELEMENT_H
#include <string>
#include "iterator.h"
#include "visitor.h"

using namespace std;
class Element{
public:
    Element(){
    }

    virtual void add(Element * s) = 0;

    virtual int size()=0;

    virtual string toString() = 0;

    virtual Iterator * createIterator() = 0;

    virtual void setOperator(char ope) = 0;

    virtual void accept(Visitor * fsv) = 0;

};
#endif