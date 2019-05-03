/* Your code here! */
#include "dsets.h"
using std::vector;

void DisjointSets::addelements(int num){
  for(int i = 0; i < num; i++){
    dset_.push_back(-1);
  }
}

int DisjointSets::find(int elem){
  if(dset_[elem] < 0){
    return elem;
  }
  else{
    int rep = find(dset_[elem]);
    dset_[elem] = rep; // path compression
    return rep;
  }
}

void DisjointSets::setunion(int a, int b){
  // find root first
  int root1 = find(a);
  int root2 = find(b);
  if(root1 == root2){
    return;
  }

  int newSize = dset_[root1] + dset_[root2];
  // if size of root1 uptree is greater
  if(dset_[root1] < dset_[root2]){
    dset_[root2] = root1;
    dset_[root1] = newSize;
  }

  else{
    dset_[root1] = root2;
    dset_[root2] = newSize;
  }
}

int DisjointSets::size(int elem){
  return -dset_[find(elem)];
}
