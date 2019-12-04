#ifndef EVALUATE_VISITOR_H
#define EVALUATE_VISITOR_H

#include <map>
#include "visitor.h"
#include "iterator.h"

class Set;
class Integer;

class EvaluateVisitor: public Visitor {
    public:
        EvaluateVisitor();
        void visitSet(Set * set);
        void visitInteger(Integer * integer);
        double getResult(){
        return 0.00;
    }    
};

#endif