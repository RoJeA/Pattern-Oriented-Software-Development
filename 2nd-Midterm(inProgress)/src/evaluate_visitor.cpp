#include "evaluate_visitor.h"
#include "set.h"
#include "integer.h"
EvaluateVisitor::EvaluateVisitor(){}

void EvaluateVisitor::visitSet(Set * set){
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
void EvaluateVisitor::visitInteger(Integer * integer){
 
}
