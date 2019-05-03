#include "disjointsets.h"
using std::vector;

/**
 * Joins the set containing a and the set containing b.
 *
 * Should use union-by-size. In case of a tie, proceed as if the set containing
 * a has larger size than the set containing b.
 */
void DisjointSets::unionBySize(int a, int b) {
  // TODO: implement this function
  int a_rep = find(a);
  int b_rep = find(b);

  if(a_rep == b_rep){
    return;
  }

  // if a has more elements
  int newSize = _data[a_rep] + _data[b_rep];
  if(_data[a_rep] <= _data[b_rep]){
    _data[b_rep] = a_rep;
    _data[a_rep] = newSize;
  }

  else{
    _data[a_rep] = b_rep;
    _data[b_rep] = newSize;
  }

}

/**
 * Finds the representative element of the set containing elem. Should compress
 * paths.
 */
int DisjointSets::find(int elem) {
  // TODO: modify this function to implement path compression
  if (_data[elem] < 0) {
    return elem;
  }
  int rep = find(_data[elem]);
  _data[elem] = rep;
  return rep;
}


/*************************************
 * PROVIDED CODE - no need to modify *
 *************************************/
void DisjointSets::makeSets(int num) {
  for (; num > 0; num--) {
    _data.push_back(-1);
  }
}

int DisjointSets::simpleFind(int elem) const {
  if (_data[elem] < 0) {
    return elem;
  }
  return simpleFind(_data[elem]);
}
