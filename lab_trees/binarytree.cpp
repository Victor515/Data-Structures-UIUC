
/**
 * @file binarytree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */

/**
 * @return The height of the binary tree. Recall that the height of a binary
 *  tree is just the length of the longest path from the root to a leaf, and
 *  that the height of an empty tree is -1.
 */
template <typename T>
int BinaryTree<T>::height() const
{
    // Call recursive helper function on root
    return height(root);
}

/**
 * Private helper function for the public height function.
 * @param subRoot
 * @return The height of the subtree
 */
template <typename T>
int BinaryTree<T>::height(const Node* subRoot) const
{
    // Base case
    if (subRoot == NULL)
        return -1;

    // Recursive definition
    return 1 + max(height(subRoot->left), height(subRoot->right));
}

/**
 * Prints out the values of the nodes of a binary tree in order.
 * That is, everything to the left of a node will be printed out before that
 * node itself, and everything to the right of a node will be printed out after
 * that node.
 */
template <typename T>
void BinaryTree<T>::printLeftToRight() const
{
    // Call recursive helper function on the root
    printLeftToRight(root);

    // Finish the line
    cout << endl;
}

/**
 * Private helper function for the public printLeftToRight function.
 * @param subRoot
 */
template <typename T>
void BinaryTree<T>::printLeftToRight(const Node* subRoot) const
{
    // Base case - null node
    if (subRoot == NULL)
        return;

    // Print left subtree
    printLeftToRight(subRoot->left);

    // Print this node
    cout << subRoot->elem << ' ';

    // Print right subtree
    printLeftToRight(subRoot->right);
}

/**
 * Flips the tree over a vertical axis, modifying the tree itself
 *  (not creating a flipped copy).
 */
template <typename T>
void BinaryTree<T>::mirror()
{
    //your code here
    mirror(root);
}

template <typename T>
void BinaryTree<T>::mirror(Node * subRoot){

  if(subRoot == NULL){
    return;
  }

  // flip left and right subtree
  mirror(subRoot->left);
  mirror(subRoot->right);

  Node * temp = subRoot->left;
  subRoot->left = subRoot->right;
  subRoot->right = temp;

}

/**
 * @return True if an in-order traversal of the tree would produce a
 *  nondecreasing list output values, and false otherwise. This is also the
 *  criterion for a binary tree to be a binary search tree.
 */
template <typename T>
bool BinaryTree<T>::isOrdered() const
{
    // your code here
    //store values in the list "in order"
    vector<T> value;
    isOrderedHelper(root, value);

    for(typename vector<T>::iterator it = value.begin(); it != value.end() - 1; it++){
      if(*it > *(it+1)){ // if any element is greater than its next element
        return false;
      }
    }

    return true;
}

template <typename T>
void BinaryTree<T>::isOrderedHelper(BinaryTree::Node* subRoot, vector<T> &treeVector) const{
    if(subRoot != NULL){
      isOrderedHelper(subRoot->left, treeVector);
      treeVector.push_back(subRoot->elem);
      isOrderedHelper(subRoot->right, treeVector);
    }
}





/**
 * creates vectors of all the possible paths from the root of the tree to any leaf
 * node and adds it to another vector.
 * Path is, all sequences starting at the root node and continuing
 * downwards, ending at a leaf node. Paths ending in a left node should be
 * added before paths ending in a node further to the right.
 * @param paths vector of vectors that contains path of nodes
 */
template <typename T>
void BinaryTree<T>::printPaths(vector<vector<T> > &paths) const
{
    // your code here

    // check for empty tree
    if(root == NULL){
      return;
    }

    vector<T> newVector;
    newVector.push_back(root->elem);

    int path_num = 0;
    if(root->left != NULL){
      paths.push_back(newVector); // left path
      printPaths(paths, root->left, path_num);
    }

    if(root->right != NULL){
      path_num++;
      paths.push_back(newVector); // right path
      printPaths(paths, root->right, path_num);
    }


}

template <typename T>
void BinaryTree<T>::printPaths(vector<vector<T> > &paths, Node* subRoot, int & path_num) const
{
  // if we reach leaf node
  if(subRoot == NULL){
    return;
  }

  paths[path_num].push_back(subRoot->elem);
  vector<T> temp;

  if(subRoot -> right != NULL){
      // store a new vector for right subtree path, if it exists
      temp = paths[path_num];
  }

  printPaths(paths, subRoot->left, path_num);

  if(subRoot ->right != NULL){
    // if right subtree exists, find its paths
    if(subRoot->left == NULL){
      printPaths(paths, subRoot->right, path_num);
    }
    else{
      paths.push_back(temp);
      path_num++;
      printPaths(paths, subRoot->right, path_num);
    }
  }

}


/**
 * Each node in a tree has a distance from the root node - the depth of that
 * node, or the number of edges along the path from that node to the root. This
 * function returns the sum of the distances of all nodes to the root node (the
 * sum of the depths of all the nodes). Your solution should take O(n) time,
 * where n is the number of nodes in the tree.
 * @return The sum of the distances of all nodes to the root
 */
template <typename T>
int BinaryTree<T>::sumDistances() const
{
    // your code here
    int sum = 0;
    sumDistances(root, sum, 0);
    return sum;

}

template <typename T>
void BinaryTree<T>::sumDistances(Node* subRoot, int & sum, int level) const{

  if(subRoot == NULL){
    return;
  }

  sum += level;
  if(subRoot->left != NULL){
    sumDistances(subRoot->left, sum, level+1);
  }

  if(subRoot->right != NULL){
    sumDistances(subRoot->right, sum, level+1);
  }



}
