// your code here
#include "LNode.h"

void LNode::lookAtMeEven(Node **arr,int n){
  for(int i = 0; i < n; i++){
    if(i % 2 == 0){
      arr[i]->setLookingAt(this);
    }
  }
}

LNode::~LNode(){
  // do nothing
}
