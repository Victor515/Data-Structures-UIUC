#include "list.h"
#include <iostream>

using namespace std;

int main() {
  List<int> list = List<int>();
  list.insertBack(5);
  list.insertBack(1);
  list.insertBack(5);
  list.insertBack(2);
  list.insertBack(7);
  list.insertBack(6);
  list.insertBack(4);
  list.print(cout);
  cout<<endl;
  list.sort();
  list.print(cout);
  cout<<endl;

/*
  List<int> list2;
  list2.insertBack(1);
  list2.insertBack(2);
  list2.insertBack(3);
  list2.print(cout);
  cout<<endl;

  list.mergeWith(list2);
  list.print(cout);
  cout<<endl;
  */
  return 0;
}
