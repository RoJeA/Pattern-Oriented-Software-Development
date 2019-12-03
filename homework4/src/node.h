#ifndef NODE_H
#define NODE_H

#include <string>
#include <sys/stat.h>
#include <fstream>
#include <dirent.h>

using namespace std;

class Node {
public:
  Node(std::string path): _path(path) {
    if(!checkExist(path)){
      //cout<<"Node not exist"<<endl;
      throw(string("Node is not exist!"));
    }
    stat(_path.c_str(), &_st);
  }

  int size() {
    return _st.st_size;
  }

  std::string fPath(){
    return _path;
  }

  virtual void addChild(Node* child) {
    throw(std::string("Invalid add!"));
  }

  virtual Node* getChild(int num) {
    return nullptr;
  }

  virtual int infoByte(){
    return size();
  }

  virtual void findfolder(std::vector<Node*> &get,string name){
    // cout<<"findfolder!"<<endl;
    // for(vector<Node*>::iterator it=_v.begin();it!=_v.end();it++){
    //   if((*it)->name()==name)
    //     get.push_back(*it);
    //   string rec = fileOrfolder((*it)->fPath());
    //   if(rec=="Folder")
    //     (*it)->findfolder(get,name);
    // }
  }

  inline bool checkExist (const std::string& path) {
      return ( access( path.c_str(), F_OK ) != -1 );
  }
  virtual std::string name()
  {
    std::size_t pos = _path.find_last_of("/\\");      // position of "/" in str
    // std::cout << " path: " << _path.substr(0,pos) << '\n';
    std::string nodename = _path.substr (pos+1);     // get from "/" to the end
    // std::cout << "->" << str3 << endl;
    return nodename;
  }

  virtual std::string findNode(std::string name)
  {
    //it's a file
    return name;
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
      // cout<<"it's a file"<<endl;
      return ("File");
    }
    else if( (_st.st_mode) & S_IFDIR )
    {
      // cout<<"it's a directory"<<endl;
      return ("Folder");
    }
    delete [] cstr;
  }
protected:
  std::string _path;
private:
  struct stat _st;
};

// //pratice here
// int infoByte(Node* node) {
//   int total = 0;
//   if (node->getChild(0) != nullptr) { //it's a folder
//     for(int i = 0; i < 2; i++){
//       total += node->getChild(i)->size();
//     }
//   }
//   return total;
// }
#endif
