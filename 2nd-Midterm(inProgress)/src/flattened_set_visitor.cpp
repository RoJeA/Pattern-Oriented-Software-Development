#include "flattened_set_visitor.h"
#include "element.h"
#include "set.h"
#include "integer.h"
FlattenedSetVisitor::FlattenedSetVisitor(){}

void FlattenedSetVisitor::visitSet(Set * set){
  Iterator* uit=set->createIterator();
  for(uit->first();!uit->isDone();uit->next()){
    Element* current=uit->currentItem();
    Set * recFolder = dynamic_cast<Set *> (uit->currentItem()); // down cast
    if(recFolder != nullptr){
      current->accept(this);
    }//else{
    //
    // }
  }
}
void FlattenedSetVisitor::visitInteger(Integer * integer){
 
}
Element * getResult(){
    return nullptr;
}    
