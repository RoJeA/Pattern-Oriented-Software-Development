#ifndef NULL_ITERATOR_H
#define NULL_ITERATOR_H

#include<string>
#include "iterator.h"
// class Node;
using namespace std;
class NullIterator:public Iterator{
public:
    bool isDone(){
        return true;
    }
    void first(){
        throw(string("no child member"));
    }
    void next(){
        throw(string("no child member"));
    }
    Node* currentItem(){
        throw(string("no child member"));
    }
};
#endif