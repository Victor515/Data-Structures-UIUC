#include "Exam.h"
#include "LNode.h"
#include <iostream>

using namespace std;

void populate(Node **arr, int n) {
    // your code here
    for(int i = 0; i < n; i++){
      LNode* newNode = new LNode();
      arr[i] = newNode;
    }
}

void lookPrev(Node **arr, int n) {
    // your code here
    for(int i = 0; i < n; i++){
      if(i == 0){
        arr[i]->setLookingAt(NULL);
      }

      else{
        arr[i]->setLookingAt(arr[i - 1]);
      }
    }
}

void display(Node **arr, int n) {
    Node *x;
    for(int i=0; i<n; i++) {
        x = arr[i]->getLookingAt();
        if (x)
            cout << "Node " << arr[i] << " is looking at " << x << "." << endl;
        else
            cout << "Node " << arr[i] << " is looking at NULL." << endl;
    }
}
