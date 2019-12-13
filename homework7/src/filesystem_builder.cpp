#include <iostream>
#include <sys/stat.h>
#include <dirent.h>
#include "filesystem_builder.h"
#include "folder.h"
#include "file.h"
#include "link.h"

using namespace std;

FileSystemBuilder* FileSystemBuilder::_fsb = nullptr;
FileSystemBuilder::FileSystemBuilder():_rootPath(nullptr){}
FileSystemBuilder * FileSystemBuilder::instance(){
  if(!_fsb){
    _fsb = new FileSystemBuilder();
  }
  return _fsb;
}
void FileSystemBuilder::build(string path){
  struct stat st;
  if (lstat(path.c_str(), &st) == 0){
    if (S_ISREG(st.st_mode))
      _rootPath = new File(path);
    else if (S_ISLNK(st.st_mode))
      _rootPath = new Link(path);
    else if (S_ISDIR(st.st_mode)){
      _rootPath = new Folder(path);
      DIR *dir = opendir(path.c_str());
      if (dir == nullptr)
        throw std::string("something get wrong--BuildFolder");

      struct dirent *dp = nullptr;
      while ((dp = readdir(dir)) != nullptr){
        if (std::string(dp->d_name) != "." && std::string(dp->d_name) != ".."){
          std::string pathString = std::string(path) + "/" + std::string(dp->d_name);
          if(dp->d_type == DT_DIR){
            FileSystemBuilder fsb;
            fsb.build(pathString.c_str());
            _rootPath->addChild(fsb.getRoot());
          }
          else if(dp->d_type == DT_REG){
            Node * inNode = new File(pathString);
            _rootPath->addChild(inNode);
          }
          else if (dp->d_type == DT_LNK){
            Node * inNode = new Link(pathString);
            _rootPath->addChild(inNode);
          }
        }
      }
      closedir(dir);
    }
  }

}
Node * FileSystemBuilder::getRoot(){
  return _rootPath;
}
