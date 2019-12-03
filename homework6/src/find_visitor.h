#ifndef FIND_VISITOR_H
#define FIND_VISITOR_H

#include <map>
#include "visitor.h"
#include "iterator.h"

class Folder;
class File;
class Link;

using namespace std;
class FindVisitor: public Visitor{
public:
  class VisitorIterator:public Iterator{
  public:
    VisitorIterator(FindVisitor * v):_v(v){

    }

    void first(){
      _current= _v->_node.begin();
    }
    void next(){
      // if iterator is to the end that it should throw string "Moving past the end!"
      // if iterator is not to the end that it should add 1
      if(_current!=_v->_node.end()){
        ++_current;;
      }
      else{
        throw(string("Moving past the end!"));
      }
    }

    bool isDone() {
      return _current == _v->_node.end();
    }
    Node* currentItem(){
      if(_current!=_v->_node.end()){
        return _current->second;
      }
      else{
        throw(string("No current item!"));
      }
    }
  private:
    map<string,Node*>::iterator _current;
    FindVisitor* _v;
};
public:
  FindVisitor(string name); // Name is the target we want to find.
  void visitFolder(Folder * folder);
  void visitFile(File * file);
  void visitLink(Link * link); // You only need to check the link itself,and you don't have to check the node that the link point to!
  string findResult();
  Iterator * createIterator();
private:
  map<string,Node*>_node;
  string _fullPath;
  string _name;
  string _result;

};

#endif
