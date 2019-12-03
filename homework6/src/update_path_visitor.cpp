#include "update_path_visitor.h"
#include "folder.h"
#include "file.h"
#include "link.h"

UpdatePathVisitor::UpdatePathVisitor(){}

void UpdatePathVisitor::visitFolder(Folder * folder){
  folder->newSelfPath(folder->getPath());
  Iterator* uit=folder->createIterator();
  for(uit->first();!uit->isDone();uit->next()){
    Node* current=uit->currentItem();
    current->newChildPath(folder->getPath());
    Folder * recFolder = dynamic_cast<Folder *> (uit->currentItem()); // down cast
    if(recFolder != nullptr){
      current->accept(this);
    }//else{
    //
    // }
  }
}
void UpdatePathVisitor::visitFile(File * file){
  file->newSelfPath(file->getPath());
}
void UpdatePathVisitor::visitLink(Link * link){
  link->newSelfPath(link->getPath());
}
