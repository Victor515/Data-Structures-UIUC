#define _BINARYTREE_CPP
#include "binarytree.h"
#include <iostream>
#include <cstdlib>

using namespace std;


template <typename T>
int BinaryTree<T>::countLeafNodes() {
  if(root == NULL){
    return 0;
  }

  int count = 0; // set up the counter
  countLeafNodes(root, count);

  return count;

}

template <typename T>
void BinaryTree<T>::countLeafNodes(Node * subroot, int & count){
  if(subroot->left == NULL && subroot->right == NULL){
    // check for leafnodes
    count += 1;
    return;
  }

  if(subroot->left != NULL){
    countLeafNodes(subroot->left, count);
  }

  if(subroot->right != NULL){
    countLeafNodes(subroot->right, count);
  }

}




/**
 * Constructor to create an empty tree.
 */
template <typename T>
BinaryTree<T>::BinaryTree() : root(NULL) {
  /* nothing */
}

/**
 * Inserts into the BinaryTree, using BST insert algorithm.
 * @param elem The element to insert
 */
template <typename T>
void BinaryTree<T>::insert(const T& elem) {
  insert(root, elem);
}

template <typename T>
void BinaryTree<T>::insert(Node*& node, const T& elem)
{
    // If we're at a NULL pointer, we can put our element here
    if (node == NULL)
        node = new Node(elem);

    // Go left or right
    else if (elem < node->elem)
        insert(node->left, elem);
    else
        insert(node->right, elem);
}
