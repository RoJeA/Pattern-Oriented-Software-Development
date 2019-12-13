#ifndef FILESYSTEM_BUILDER_H
#define FILESYSTEM_BUILDER_H
#include <string>
using namespace std;

class Node;
class FileSystemBuilder  {
protected:
  FileSystemBuilder();
public:
  static FileSystemBuilder * instance();
  void build(string path);
  Node * getRoot();
private:
  Node* _rootPath;
  static FileSystemBuilder * _fsb;
};

#endif
