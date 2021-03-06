#include "TreeNode.h"

// Your function here

TreeNode *makeFullRight(int n) {
  // set count to 1 and start building the tree
  int count = 1;
  TreeNode* root = makeFullRight(n, count);
  return root;
}

TreeNode * makeFullRight(int n, int & count){

  if(n == count){
    return new TreeNode(count, NULL, NULL);
  }

  // if n != count
  TreeNode * curr = new TreeNode();
  curr->data_ = count++;
  curr->left_ = new TreeNode(count++, NULL, NULL);
  curr->right_ = makeFullRight(n, count);

  return curr;

}

// Methods and functions we provide following.
// You should not need to edit this code.

TreeNode::TreeNode(int data, TreeNode *left, TreeNode *right) :
    data_(data), left_(left), right_(right) {}

TreeNode::~TreeNode() {
    if (left_ != NULL)
        delete left_;
    if (right_ != NULL)
        delete right_;
}

bool equal(TreeNode *n1, TreeNode *n2) {
    if (n1 == NULL)
        return n2 == NULL;

    if (n2==NULL)
        return false;

    return (n1->getData() == n2->getData() &&
            equal(n1->getLeft(),n2->getLeft()) &&
            equal(n1->getRight(),n2->getRight()));
}

int TreeNode::getData() const {
    return data_;
}

TreeNode *TreeNode::getLeft() const {
    return left_;
}

TreeNode *TreeNode::getRight() const {
    return right_;
}
