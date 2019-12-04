#ifndef INTEGER_H
#define INTEGER_H

#include <string>
#include "element.h"
#include "null_iterator.h"
using namespace std;
class Integer:public Element{
public:
    Integer(int i){
        if(static_cast<int>(i)){
         _i=i;
        }
    }

    int value(){
        return _i;
    }
    void add(Element * element){
        throw string("It's an integer!");
    }
    int size(){
        return 1;
    }
    std::string toString(){
        return to_string(_i);
    }
    Iterator * createIterator(){
        return new NullIterator();
    }
    void setOperator(char c){
        throw string("Cannot set operator on it!");
    }
    void accept(Visitor * visitor){}
private:
    int _i;
};

#endif