#include <iostream>
using namespace std;
#include <regex>
#include "find_visitor.h"

#include "link.h"
#include "folder.h"
#include "file.h"


FindVisitor::FindVisitor(string name): _fullPath("") , _name(name),_result(""){

}
void FindVisitor::visitFolder(Folder * folder){
  if(_fullPath == ""){
    _fullPath = folder->getPath();
    _node.clear();

  }
  Iterator *fit=folder->createIterator();
  for(fit->first();!fit->isDone();fit->next()){
    if(_name==fit->currentItem()->name()){
      // cout<<"put!!"<<endl;
      _node.insert(pair<string, Node*>(fit->currentItem()->getPath(),fit->currentItem()));
    }
    Folder * recFolder = dynamic_cast<Folder *> (fit->currentItem()); // down cast
    if(recFolder != nullptr){
      fit->currentItem()->accept(this);
    }
  }
}
void FindVisitor::visitFile(File * file){
  _node.clear();
  if(file->name()==_name)
    _result=file->name();
  else _result="";
}
void FindVisitor::visitLink(Link * link){
// You only need to check the link itself,and you don't have to check the node that the link point to!
  _node.clear();
  if(link->name()==_name)
    _result=link->name();
  else _result="";
}
string FindVisitor::findResult(){
  Iterator* it=this->createIterator();
  int count;
  for(it->first(),count=0;!it->isDone();it->next(),count++){
      Node* node=it->currentItem();
      string nodePath=node->getPath();

      regex patten_parent(_fullPath);
      regex patten_targetName(_name);
      std::smatch m;
      if(regex_search(nodePath,m,patten_parent)){
        _result+="."+m.suffix().str();
        if(count==_node.size()-1)break;
          _result+="\n";
      }
  }
  string stemp=_result;
  _result="";
  this->_node.clear();;
  this->_fullPath="";
  return stemp;
}

Iterator* FindVisitor::createIterator(){
    return new FindVisitor::VisitorIterator(this);
}
