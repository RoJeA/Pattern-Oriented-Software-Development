#ifndef FOLDER_H
#define FOLDER_H

#include <string>
#include <sys/stat.h>
#include <vector>

#include "node.h"

class Folder: public Node {
public:
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
    _v.push_back(child);
  }

  Node* getChild(int num) {
    return _v[num];
  }

  int infoByte() {
    int total = 0;
    for(int i = 0; i < _v.size(); i++){
      total += _v.at(i)->infoByte();
    }
    return total;
  }

  std::string findNode(std::string name){
    // implementation findNode
    // folder->findNode(name) that should find all nodes(include child nodes and all offspring) under it.
    // file->findNode(name) that should find itself.
    // if find two nodes or more than two nodes.
    // Result should be separated by '\n'.
    std::vector<Node*> get;
    string allFile="";
    findfolder(get,name);
    std::string topPath = this->name();
    // cout<<"gettttttttttt : "<<get.size()<<endl;
    if(get.size()>1){
      for(vector<Node*>::iterator it=get.begin();it!=get.end();it++){
        string cut=(*it)->fPath();
        // cout<<"fPathhhhhh : "<<cut<<endl;
        std::size_t pos = cut.find("/"+topPath);      // position of "/" in str
        allFile += "."+cut.substr (pos+topPath.size()+1);     // get from "/" to the end
        // cout<<"allllllll : "<<allFile<<endl;
        if(it!=get.end()-1)
          allFile += "\n";
      }

    }
    else if(get.size() == 1){
      allFile+="./"+name;
    }
    // cout<<"get.size()"<<get.size()<<endl;
    return allFile;


    // findFile.find()
    // cout<<findFile<<endl;
    // return allFile;
  }
  std::string listNode(){
    string folderList="";
    sort(_v.begin(),_v.end(),[](Node* a,Node* b){
      return a->name() < b->name();
    });
    for(vector<Node*>::iterator it=_v.begin();it!=_v.end();it++){
      folderList += (*it)->name();
      // cout<<"(*it)========"<<(*it)->name()<<endl;
      if(it!=_v.end()-1){
        folderList+=" ";
      }
    }
    return folderList;
  }
  void findfolder(std::vector<Node*> &get,string name){
    // cout<<"findfolder!"<<endl;
    for(vector<Node*>::iterator it=_v.begin();it!=_v.end();it++){
      if((*it)->name()==name)
        get.push_back(*it);
      string rec = fileOrfolder((*it)->fPath());
      if(rec=="Folder")
        (*it)->findfolder(get,name);
    }
  }

private:
  std::vector<Node*> _v;
  struct stat _s;
};
#endif
