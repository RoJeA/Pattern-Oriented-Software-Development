#ifndef FILE_H
#define FILE_H

#include <string>
#include <sys/stat.h>
#include <unistd.h>

#include "node.h"
#include "null_iterator.h"
#include "visitor.h"
class File: public Node {
public:
  File(std::string path): Node(path){
    char *cstr = new char[path.length() + 1];
    strcpy(cstr, path.c_str());
    stat(cstr, &_s);
    if( (_s.st_mode) & S_IFDIR )
    {
        //it's a directory
      throw(string("It is not File!"));
    }
    delete [] cstr;
  }
  Iterator* createIterator(){
    return new NullIterator();
  }
  void accept(Visitor* visitor){
    visitor->visitFile(this);
  }
private:
  struct stat _s;
};

#endif
