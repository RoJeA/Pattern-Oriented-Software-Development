#ifndef FOLDER_H
#define FOLDER_H

#include <string>
#include <sys/stat.h>
#include <map>

#include "node.h"
#include "visitor.h"

class Folder: public Node {
public:
  class FolderIterator:public Iterator {
  public:
    FolderIterator(Folder * f): _f(f) {}

    void first() {
      _current = _f->_v.begin();
      // _current = *(_f->_v.begin());
    }

    Node * currentItem() {
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
    Folder * _f;
    std::map<string,Node *>::iterator _current;
  };
  Folder(std::string path): Node(path) {
    char *cstr = new char[path.length() + 1];
    strcpy(cstr, path.c_str());
    stat(cstr, &_s);
    if( _s.st_mode & S_IFREG  )
    {
      //it's a file
      throw(string("It is not Folder!"));
    }
    delete [] cstr;
  }

  void addChild(Node* child) {
    _v.insert(std::pair<string,Node*>(child->name(),child));
  }
  // Node* getChild(string name) {
  //   return _v[name];
  // }
  int infoByte() {
    int total = 0;
    for(map<string,Node*>::iterator i=_v.begin();i!=_v.end();i++){
      total += i->second->infoByte();
    }
    return total;
  }
  Iterator * createIterator() {
    return new FolderIterator(this);
  }
  void accept(Visitor * visitor){
    visitor->visitFolder(this);
  }

private:
  std::map<string,Node*> _v;
  struct stat _s;
};
#endif
