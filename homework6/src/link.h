#ifndef LINK_H
#define LINK_H

#include<string>
#include <sys/stat.h>
#include "node.h"
#include "null_iterator.h"
#include "visitor.h"
using namespace std;
class Link: public Node {
public:
  Link(string path, Node * node=nullptr): Node(path){
    struct stat buf;
    int x;
    x = lstat (path.c_str(), &buf);
    if (!S_ISLNK(buf.st_mode))
      throw(string("It is not Link!"));
    addLink(node);
  } // You should check path if it is not a link that you should throw string "It is not Link!"

  void addLink(Node * node){
    _node = node;
  } // add symbolic link

  Node * getSource(){
    return _node;
  } // return node that the link point to!

  Iterator* createIterator(){
    return new NullIterator();
  } // return null Iterator

  void accept(Visitor* visitor){
    visitor->visitLink(this);
  } // accept visitor
private:
  Node* _node;
  struct stat _st;

};

#endif
