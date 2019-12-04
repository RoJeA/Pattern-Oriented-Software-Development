#ifndef FLATTENED_SET_VISITOR_H
#define FLATTENED_SET_VISITOR_H
#include "visitor.h"
class Set;
class Integer;
class Element;

class FlattenedSetVisitor: public Visitor {
public:
    FlattenedSetVisitor();
    void visitSet(Set * set);
    void visitInteger(Integer * integer);
    Element * getResult(){};
};

#endif