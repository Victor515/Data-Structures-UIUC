/**
 * @file list.cpp
 * Doubly Linked List (MP 3).
 */

/**
 * Destroys the current List. This function should ensure that
 * memory does not leak on destruction of a list.
 */
template <class T>
List<T>::~List() {
  /// @todo Graded in MP3.1
  clear();
}

/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
template <class T>
void List<T>::clear() {
  /// @todo Graded in MP3.1
  // check for empty list
  if(this->size() == 0){
    return;
  }
  ListNode* curr = head_;
  while(curr->next != NULL){
    curr = curr->next;
    delete curr->prev;
  }

  // delete the tail of the List
  delete curr;

  // set head and tail to NULL
  head_ = NULL;
  tail_ = NULL;
}

/**
 * Inserts a new node at the front of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <class T>
void List<T>::insertFront(T const& ndata) {
  /// @todo Graded in MP3.1

  // to check if the List is empty
  if(head_ == NULL){
    head_ = new ListNode(ndata);
    tail_ = head_;
    length_ = 1;
  }

  else{
    ListNode * newNode = new ListNode(ndata);
    newNode->next = head_;
    head_->prev = newNode;
    head_ = newNode;
    length_++;
  }
}

/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <class T>
void List<T>::insertBack(const T& ndata) {
  /// @todo Graded in MP3.1
  if(head_ == NULL){
    head_ = new ListNode(ndata);
    tail_ = head_;
    length_ = 1;
  }
  else{
    ListNode * newNode = new ListNode(ndata);
    newNode->prev = tail_;
    tail_->next = newNode;
    tail_ = newNode;
    length_++;
  }
}

/**
 * Reverses the current List.
 */
template <class T>
void List<T>::reverse() {
  reverse(head_, tail_);
}

/**
 * Helper function to reverse a sequence of linked memory inside a List,
 * starting at startPoint and ending at endPoint. You are responsible for
 * updating startPoint and endPoint to point to the new starting and ending
 * points of the rearranged sequence of linked memory in question.
 *
 * @param startPoint A pointer reference to the first node in the sequence
 *  to be reversed.
 * @param endPoint A pointer reference to the last node in the sequence to
 *  be reversed.
 */
template <class T>
void List<T>::reverse(ListNode*& startPoint, ListNode*& endPoint) {
    /// @todo Graded in MP3.1

    // check for empty list
    if(this->size() == 0){
      return;
    }
    //set up two loop node
    ListNode* iter_start = startPoint;
    ListNode* iter_end = endPoint;

    while(iter_start != iter_end  && iter_start->next != iter_end){
      // for manipulating current node
      ListNode* temp1 = iter_start;
      ListNode* temp2 = iter_end;
      ListNode* temp1_next = temp1->next;
      ListNode* temp2_prev = temp2->prev;

      if(temp1 == head_){
        if(temp2 == tail_){
          temp1->next = NULL;
          temp1->prev = temp2_prev;
          temp2->prev = NULL;
          temp2->next = temp1_next;
          temp2_prev->next = temp1;
          temp1_next->prev = temp2;
          head_ = temp2;
          tail_ = temp1;
        }

        else{//temp1 == head_ while temp2 != tail_
          ListNode* temp2_next = temp2->next;
          temp1->next = temp2_next;
          temp1->prev = temp2_prev;
          temp2->prev = NULL;
          temp2->next = temp1_next;
          temp2_prev->next = temp1;
          temp1_next->prev = temp2;
          head_ = temp2;
          temp2_next->prev = temp1;
        }
      }

      else{
        if(temp2 == tail_){//temp1 != head_ while temp2 == tail_
          ListNode* temp1_prev = temp1->prev;
          temp1->next = NULL;
          temp1->prev = temp2_prev;
          temp2->prev = temp1_prev;
          temp2->next = temp1_next;
          temp2_prev->next = temp1;
          temp1_next->prev = temp2;
          temp1_prev->next = temp2;
          tail_ = temp1;


        }

        else{
          ListNode* temp1_prev = temp1->prev;
          ListNode* temp2_next = temp2->next;
          temp1->next = temp2_next;
          temp1->prev = temp2_prev;
          temp2->prev = temp1_prev;
          temp2->next = temp1_next;
          temp2_prev->next = temp1;
          temp1_next->prev = temp2;
          temp1_prev->next = temp2;
          temp2_next->prev = temp1;



        }

      }

      iter_start = temp1_next;
      iter_end = temp2_prev;


    }

    // handle the case iter_start->next == iter_end
    // a bug here not considering the head tail case(when there is only two node)
    if(iter_start->next == iter_end){
      if(iter_start == head_){

        if(iter_end == tail_){
          iter_start->prev = iter_end;
          iter_end->next = iter_start;
          iter_start->next = NULL;
          iter_end->prev = NULL;
          head_ = iter_end;
          tail_ = iter_start;
        }

        else{//iter_end is not the tail_
          iter_start->next = iter_end->next;
          iter_end->next->prev = iter_start;
          iter_end->prev = NULL;
          head_ = iter_end;
          iter_start->prev = iter_end;
          iter_end->next = iter_start;
        }
      }
      else{
        if(iter_end == tail_){//iter_start is not the head_
          iter_start->next = NULL;
          tail_ = iter_start;
          iter_end->prev = iter_start->prev;
          iter_start->prev->next = iter_end;
          iter_start->prev = iter_end;
          iter_end->next = iter_start;
        }

        else{
          iter_start->next = iter_end->next;
          iter_end->next->prev = iter_start;
          iter_end->prev = iter_start->prev;
          iter_start->prev->next = iter_end;
          iter_start->prev = iter_end;
          iter_end->next = iter_start;
        }
      }
    }

    /*
    ListNode* swap_temp = startPoint;
    startPoint = endPoint;
    endPoint = swap_temp;
*/

}

/**
 * Reverses blocks of size n in the current List. You should use your
 * reverse( ListNode * &, ListNode * & ) helper function in this method!
 *
 * @param n The size of the blocks in the List to be reversed.
 */
template <class T>
void List<T>::reverseNth(int n) {
  /// @todo Graded in MP3.1
  // check for empty list
  if(this->size() == 0){
    return;
  }

  ListNode* curr = head_;


  while(curr != NULL){
    ListNode* curr0th = curr;
    ListNode* currNth = curr;
    int count = 0;
    while(count != n -1 && currNth != tail_){
      currNth = currNth->next;
      count++;
    }
    curr = currNth->next;

    if(curr0th != tail_){// if curr0th and currNth do not both point tail_
      reverse(curr0th,currNth);
    }
  }
}

/**
 * Modifies the List using the waterfall algorithm.
 * Every other node (starting from the second one) is removed from the
 * List, but appended at the back, becoming the new tail. This continues
 * until the next thing to be removed is either the tail (**not necessarily
 * the original tail!**) or NULL.  You may **NOT** allocate new ListNodes.
 * Note that since the tail should be continuously updated, some nodes will
 * be moved more than once.
 */
template <class T>
void List<T>::waterfall() {
  /// @todo Graded in MP3.1

  // check for empty list
  if(this->size() == 0){
    return;
  }

  ListNode* curr = head_->next;
  while(curr != NULL && curr != tail_){
    ListNode* temp = curr;
    curr = curr->next->next;
    temp->prev->next = temp->next;
    temp->next->prev = temp->prev;
    temp->next = NULL;
    temp->prev = tail_;
    tail_->next = temp;
    tail_ = temp;
  }
}

/**
 * Splits the given list into two parts by dividing it at the splitPoint.
 *
 * @param splitPoint Point at which the list should be split into two.
 * @return The second list created from the split.
 */
template <class T>
List<T> List<T>::split(int splitPoint) {
    if (splitPoint > length_)
        return List<T>();

    if (splitPoint < 0)
        splitPoint = 0;

    ListNode* secondHead = split(head_, splitPoint);

    int oldLength = length_;
    if (secondHead == head_) {
        // current list is going to be empty
        head_ = NULL;
        tail_ = NULL;
        length_ = 0;
    } else {
        // set up current list
        tail_ = head_;
        while (tail_->next != NULL)
            tail_ = tail_->next;
        length_ = splitPoint;
    }

    // set up the returned list
    List<T> ret;
    ret.head_ = secondHead;
    ret.tail_ = secondHead;
    if (ret.tail_ != NULL) {
        while (ret.tail_->next != NULL)
            ret.tail_ = ret.tail_->next;
    }
    ret.length_ = oldLength - splitPoint;
    return ret;
}

/**
 * Helper function to split a sequence of linked memory at the node
 * splitPoint steps **after** start. In other words, it should disconnect
 * the sequence of linked memory after the given number of nodes, and
 * return a pointer to the starting node of the new sequence of linked
 * memory.
 *
 * This function **SHOULD NOT** create **ANY** new List objects!
 *
 * @param start The node to start from.
 * @param splitPoint The number of steps to walk before splitting.
 * @return The starting node of the sequence that was split off.
 */
template <class T>
typename List<T>::ListNode* List<T>::split(ListNode* start, int splitPoint) {
    /// @todo Graded in MP3.2

    // check for empty list
    if(start == NULL){
      return NULL; // return NULL if given an empty list
    }


    for(int i = 0; i < splitPoint; i++){
      start = start->next; // let start point to the starting node of the sublist
    }

    start->prev->next = NULL;
    start->prev = NULL;


    return start;
}

/**
 * Merges the given sorted list into the current sorted list.
 *
 * @param otherList List to be merged into the current list.
 */
template <class T>
void List<T>::mergeWith(List<T>& otherList) {
    // set up the current list
    head_ = merge(head_, otherList.head_);
    tail_ = head_;

    // make sure there is a node in the new list
    if (tail_ != NULL) {
        while (tail_->next != NULL)
            tail_ = tail_->next;
    }
    length_ = length_ + otherList.length_;

    // empty out the parameter list
    otherList.head_ = NULL;
    otherList.tail_ = NULL;
    otherList.length_ = 0;
}

/**
 * Helper function to merge two **sorted** and **independent** sequences of
 * linked memory. The result should be a single sequence that is itself
 * sorted.
 *
 * This function **SHOULD NOT** create **ANY** new List objects.
 *
 * @param first The starting node of the first sequence.
 * @param second The starting node of the second sequence.
 * @return The starting node of the resulting, sorted sequence.
 */
template <class T>
typename List<T>::ListNode* List<T>::merge(ListNode* first, ListNode* second) {
  /// @todo Graded in MP3.2

  if (first == NULL){
    return second;
  }

  if (second == NULL){
    return first;
  }

  // create a node pointer for list1
  // this saves some time iterating through list 1 to find insterting point
  ListNode * curr_1 = first;

  while(second != NULL){

    // iterate through list 1 to find where to insert or gp tp the last element
    while(curr_1->next != NULL){

      if(curr_1 -> data < second -> data){
        curr_1 = curr_1 -> next;
      }

      else{
        break;
      }
    }

    if(curr_1->next == NULL){// if we go to the end of list1
      if(curr_1 -> data < second -> data){
        curr_1->next = second;
        second->prev = curr_1;
        break;
      }

      else if(curr_1->prev == NULL){
        //handle a special case where list has only one element which is
        // greater than any element in list2
        // note: this block only executes once
        ListNode* temp = second->next;
        curr_1->prev = second;
        second->next = curr_1;
        first = second;
        curr_1 = first; // add this line to make curr_1 go to the list1 head again
        second = temp;
        continue;
      }
    }

    ListNode* temp = second->next; // temp node for next pointer in list 2

    if(curr_1 == first){ // if element in list2 is small than any element in list1
      curr_1->prev = second;
      second->next = curr_1;
      first = second;
    }
    else{
      curr_1->prev->next = second;
      second->prev = curr_1->prev;
      second->next = curr_1;
      curr_1->prev = second;
    }
    second = temp;
  }

  return first;
}

/**
 * Sorts the current list by applying the Mergesort algorithm.
 */
template <class T>
void List<T>::sort() {
    if (empty())
        return;
    head_ = mergesort(head_, length_);
    tail_ = head_;
    while (tail_->next != NULL)
        tail_ = tail_->next;
}

/**
 * Sorts a chain of linked memory given a start node and a size.
 * This is the recursive helper for the Mergesort algorithm (i.e., this is
 * the divide-and-conquer step).
 *
 * @param start Starting point of the chain.
 * @param chainLength Size of the chain to be sorted.
 * @return A pointer to the beginning of the now sorted chain.
 */
template <class T>
typename List<T>::ListNode* List<T>::mergesort(ListNode* start, int chainLength) {
    /// @todo Graded in MP3.2

    if(chainLength == 1){
      return start;
    }

    ListNode* start_2 = split(start, chainLength / 2);
    start = mergesort(start, chainLength / 2);
    start_2 = mergesort(start_2, chainLength - chainLength / 2);
    ListNode* result = merge(start, start_2);
    return result;
}
