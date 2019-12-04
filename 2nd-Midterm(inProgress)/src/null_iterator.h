#ifndef NULL_ITERATOR_H
#define NULL_ITERATOR_H

#include<string>
#include "iterator.h"

using namespace std;
class NullIterator:public Iterator{
public:
    bool isDone(){
        return true;
    }
    void first(){
        throw(string("No child member!"));
    }
    void next(){
        throw(string("No child member!"));
    }
    Element* currentItem(){
        throw(string("No child member!"));
    }
};
#endif
