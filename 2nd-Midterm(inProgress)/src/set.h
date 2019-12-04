#ifndef SET_H
#define SET_H

#include <string>
#include <sys/stat.h>
#include <map>

#include "element.h"
#include "iterator.h"
using namespace std;
class Set:public Element{
public:
  class SetIterator:public Iterator {
  public:
    SetIterator(Set * f): _f(f) {}

    void first() {
      _current = _f->_v.begin();
      // _current = *(_f->_v.begin());
    }

    Element * currentItem() {
      // if iterator is to the end that it should throw string "No current item!"
      // if iterator is not to the end that it should return current node
      if(_current!=_f->_v.end()){
        return _current->second;
      }
      else{
        throw(string("No current item!"));
      }
    }

    void next() {
      // if iterator is to the end that it should throw string "Moving past the end!"
      // if iterator is not to the end that it should add 1
      if(_current!=_f->_v.end()){
        ++_current;;
      }
      else{
        throw(string("Moving past the end!"));
      }
    }

    bool isDone() {
      return _current == _f->_v.end();
    }

  private:
    Set * _f;
    std::map<string,Element *>::iterator _current;
  };

//(1)
    Set(){}
//(2)
    void add(Element * element){
        _v.insert(std::pair<string,Element*>("element",element));
    }
//(3)
    int size(){
    int total = 1;
    Iterator* i=this->createIterator();
    for(i->first();!i->isDone();i->next()){
        Set * set = dynamic_cast<Set *> (i->currentItem()); // down cast
        if(set!=nullptr){
            total+=this->size();            
        }
        total ++;
    }
    return total;
    }
//(4)
    std::string toString(){
        // Set * set = dynamic_cast<Set *> (_v); // down cast            
        // if(set!=nullptr){
        //     Iterator* it=this->createIterator();
        //     int count;
        //     string fullname="{";
        //     cout<<"iterator currrent item:"<< it-><<endl;     
        //     for(it->first(),count=0;!it->isDone();it->next(),count++){
        //         cout<<"Full Set:"<<fullname<<endl;
        //     }
        //     fullname = fullname + to_string(1);
        //     cout<<"Full Set:"<<fullname<<endl;
        // }
        // else{
        //     fullname = fullname + to_string(1)+"}";
        //     cout<<"Full Set:"<<fullname<<endl;
        // }

        // return fullname;
        return "{1}";
    }
//(5)
    Iterator * createIterator(){
        return new SetIterator(this);
    }
//(6)
    void setOperator(char ope){
        if(ope=='+'||ope=='-'||ope=='*'||ope=='/'){
            
        }
        else{
            throw string("Invalid operator!");
        }
    }
//(7)
    void accept(Visitor * visitor){}
private:
  std::map<string,Element*> _v;
};
#endif
