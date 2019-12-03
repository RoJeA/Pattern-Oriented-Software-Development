#ifndef NODE_H
#define NODE_H

#include <string>
#include <sys/stat.h>
#include <fstream>
#include <dirent.h>
#include <unistd.h>
#include <cstdio>
#include <cstring>
#include "iterator.h"
#include "visitor.h"

using namespace std;

class Node {
public:
  Node(std::string path): _path(path) {
    if(!checkExist(path)){
      throw(string("Node is not exist!"));
    }
    stat(_path.c_str(), &_st);

    //name
    std::size_t pos = _path.find_last_of("/\\");      // position of "/" in str
    std::string nodename = _path.substr (pos+1);     // get from "/" to the end
    _name = nodename;
  }
  virtual ~Node(){}
  int size() {
    return _st.st_size;
  }

  std::string getPath(){
    return _path;
  }

  virtual void addChild(Node* child) {
    throw(std::string("Invalid add!"));
  }

  // virtual Node* getChild(int num) {
  //   return nullptr;
  // }

  virtual Iterator* createIterator()=0;

  virtual int infoByte(){
    return size();
  }

  inline bool checkExist (const std::string& path) {
      return ( access( path.c_str(), F_OK ) != -1 );
  }
  virtual std::string name()
  {
    return _name;
  }

  virtual std::string listNode()
  {
    throw(std::string("Not a directory"));
    return nullptr;
  }
  virtual std::string fileOrfolder(std::string name)
  {
    char *cstr = new char[name.length() + 1];
    strcpy(cstr, name.c_str());
    stat(cstr, &_st);
    if( _st.st_mode & S_IFREG  )
    {
      return ("File");
    }
    else if( (_st.st_mode) & S_IFDIR )
    {
      return ("Folder");
    }
    delete [] cstr;
    return nullptr;
  }
  virtual void accept(Visitor* visitor){
      throw(string("Wrong Visit!"));
    } // accept visitor
  void renameNode(string new_name){
    std::size_t pos = _path.find_last_of("/\\");      // position of "/" in str
    string newP = _path.substr (0,pos) + "/" + new_name;
    std::rename(_path.c_str(), newP.c_str());
    _name = new_name;
    /* You should update
      1. The physical node name.
      2. The node name in your own file system
    */
  }
  void newSelfPath(string oldpath){
    std::size_t pos = oldpath.find_last_of("/\\");      // position of "/" in str
    this->_path = oldpath.substr (0,pos) + "/" + _name;
  }
  void newChildPath(string oldpath){
    this->_path = oldpath+ "/" + _name;
  }
protected:
  std::string _path;
private:
  struct stat _st;
  std::string _name;
};

#endif
