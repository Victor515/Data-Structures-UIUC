/**
 * @file avltree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */

template <class K, class V>
V AVLTree<K, V>::find(const K& key) const
{
    return find(root, key);
}

template <class K, class V>
V AVLTree<K, V>::find(Node* subtree, const K& key) const
{
    if (subtree == NULL)
        return V();
    else if (key == subtree->key)
        return subtree->value;
    else {
        if (key < subtree->key)
            return find(subtree->left, key);
        else
            return find(subtree->right, key);
    }
}

template <class K, class V>
void AVLTree<K, V>::rotateLeft(Node*& t)
{
    functionCalls.push_back("rotateLeft"); // Stores the rotation name (don't remove this)
    // your code here
    Node * mid = t -> right;
    t->right = mid->left;
    mid->left = t;
    t = mid;
}

template <class K, class V>
void AVLTree<K, V>::rotateLeftRight(Node*& t)
{
    functionCalls.push_back("rotateLeftRight"); // Stores the rotation name (don't remove this)
    // Implemented for you:
    rotateLeft(t->left);
    rotateRight(t);
}

template <class K, class V>
void AVLTree<K, V>::rotateRight(Node*& t)
{
    functionCalls.push_back("rotateRight"); // Stores the rotation name (don't remove this)
    // your code here
    Node * mid = t -> left;
    t -> left = mid -> right;
    mid -> right = t;
    t = mid;
}

template <class K, class V>
void AVLTree<K, V>::rotateRightLeft(Node*& t)
{
    functionCalls.push_back("rotateRightLeft"); // Stores the rotation name (don't remove this)
    // your code here
    rotateRight(t->right);
    rotateLeft(t);
}

template <class K, class V>
void AVLTree<K, V>::rebalance(Node*& subtree)
{
    // your code here

    // calculate balance factor
    int balance = heightOrNeg1(subtree->right) - heightOrNeg1(subtree->left);
    //std::cout<<subtree->key<<':'<<heightOrNeg1(subtree->right)<<':'<<heightOrNeg1(subtree->left)<<std::endl;

    // case 1: right subtree needs rebalancing
    if(balance == 2){
      int rightbalance = heightOrNeg1(subtree->right->right) - heightOrNeg1(subtree->right->left);

      if(rightbalance >= 0){
        // case to do a left rotation
        rotateLeft(subtree);
      }

      else{
        rotateRightLeft(subtree);
      }
    }

    // case 2: left subtree needs rebalancing
    else if(balance == -2){
      int leftbalance = heightOrNeg1(subtree->left->right) - heightOrNeg1(subtree->left->left);

      if(leftbalance <= 0){
        // case to do a right rotation
        rotateRight(subtree);
      }

      else{
        rotateLeftRight(subtree);
      }

    }


    // this remains in doubt: do I need to update all childnodes?
    updateHeight(root);

}

template <class K, class V>
void AVLTree<K, V>::insert(const K & key, const V & value)
{
    insert(root, key, value);
}

template <class K, class V>
void AVLTree<K, V>::insert(Node*& subtree, const K& key, const V& value)
{
    // your code here
    if(subtree == NULL){
      // the base case
      subtree = new Node(key, value);
    }

    else if(key < subtree->key){
      // go left
      insert(subtree->left, key , value);
    }

    else if(key > subtree->key){
      // go right
      insert(subtree->right, key, value);
    }


    // rebalance at each level
    rebalance(subtree);

}

template <class K, class V>
void AVLTree<K, V>::remove(const K& key)
{
    remove(root, key);
}

template <class K, class V>
void AVLTree<K, V>::remove(Node*& subtree, const K& key)
{
    if (subtree == NULL)
        return;

    if (key < subtree->key) {
        // your code here
        remove(subtree->left, key);
        // rebalance at each level
        rebalance(subtree);
    } else if (key > subtree->key) {
        // your code here
        remove(subtree->right, key);
        // rebalance at each level
        rebalance(subtree);
    } else {
        if (subtree->left == NULL && subtree->right == NULL) {
            /* no-child remove */
            // your code here
            delete subtree;
            subtree = NULL;

        } else if (subtree->left != NULL && subtree->right != NULL) {
            /* two-child remove */
            // your code here

            // step 1: find IOP
            Node* iop = findIOP(subtree->left);

            // step 2: swap removal with iop(key and value)
            swap(subtree, iop);

            // delete iop and rebalance at each level
            remove(subtree->left,key);
            rebalance(subtree);

        } else {
            /* one-child remove */
            // your code here
            Node * temp = subtree;

            if(subtree->left != NULL){
              subtree = subtree->left;
            }

            else if(subtree->right != NULL){
              subtree = subtree -> right;
            }

            delete temp;
        }
        // your code here
    }


}

template <class K, class V>
int AVLTree<K, V>::height(const Node * root){
	if(root == NULL){
		// base case
		return -1;
	}

	int left_height = height(root->left);
	int right_height = height(root->right);

	if(left_height >= right_height){
		return (left_height + 1);
	}

	else{
		return (right_height + 1);
	}

}

template <class K, class V>
typename AVLTree<K, V>::Node* AVLTree<K, V>::findIOP(Node* node){
  Node * current = node;

  while(current->right != NULL){
    // always go right
    current = current->right;
  }

  return current;
}

template <class K, class V>
void AVLTree<K, V>::updateHeight(Node * root){
  if(root == NULL){
    return;
  }

  updateHeight(root->left);
  updateHeight(root->right);
  root->height = max(height(root->left), height(root->right)) + 1;

}
