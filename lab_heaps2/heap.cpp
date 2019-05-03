
/**
 * @file heap.cpp
 * Implementation of a heap class.
 */

template <class T, class Compare>
size_t heap<T, Compare>::root() const
{
    /// @todo Update to return the index you are choosing to be your root.

    // I choose to use a setinel node
    return 1;
}

template <class T, class Compare>
size_t heap<T, Compare>::leftChild(size_t currentIdx) const
{
    /// @todo Update to return the index of the left child.

    return (currentIdx * 2);
}

template <class T, class Compare>
size_t heap<T, Compare>::rightChild(size_t currentIdx) const
{
    /// @todo Update to return the index of the right child.
    return (currentIdx * 2 + 1);
}

template <class T, class Compare>
size_t heap<T, Compare>::parent(size_t currentIdx) const
{
    /// @todo Update to return the index of the parent.
    return (currentIdx / 2);
}

template <class T, class Compare>
bool heap<T, Compare>::hasAChild(size_t currentIdx) const
{
    /// @todo Update to return whether the given node has a child

    // check if current node's left child exists
    return (currentIdx * 2 < _elems.size());
}

template <class T, class Compare>
size_t heap<T, Compare>::maxPriorityChild(size_t currentIdx) const
{
    /// @todo Update to return the index of the child with highest priority
    ///   as defined by higherPriority()

    if(currentIdx * 2 + 1 >= _elems.size()){
      // if rightChild does not exist
      return (currentIdx * 2);
    }

    else{
      if( higherPriority(_elems[currentIdx * 2], _elems[currentIdx * 2 + 1]) ){
        return (currentIdx * 2);
      }

      else{
        return (currentIdx * 2 + 1);
      }
    }
}

template <class T, class Compare>
void heap<T, Compare>::heapifyDown(size_t currentIdx)
{
    /// @todo Implement the heapifyDown algorithm.

    if(hasAChild(currentIdx)){
      size_t minChildIndex = maxPriorityChild(currentIdx);

      // if min child has higher priority
      if( higherPriority(_elems[minChildIndex], _elems[currentIdx]) ){
        // do the swap
        T temp = _elems[minChildIndex];
        _elems[minChildIndex] = _elems[currentIdx];
        _elems[currentIdx] = temp;

        // keep recursing down
        heapifyDown(minChildIndex);
      }
    }
}

template <class T, class Compare>
void heap<T, Compare>::heapifyUp(size_t currentIdx)
{
    if (currentIdx == root())
        return;
    size_t parentIdx = parent(currentIdx);
    if (higherPriority(_elems[currentIdx], _elems[parentIdx])) {
        std::swap(_elems[currentIdx], _elems[parentIdx]);
        heapifyUp(parentIdx);
    }
}

template <class T, class Compare>
heap<T, Compare>::heap()
{
    /// @todo Depending on your implementation, this function may or may
    ///   not need modifying

    // add a sentinel node at the 0 index
    _elems.push_back(T());
}

template <class T, class Compare>
heap<T, Compare>::heap(const std::vector<T>& elems)
{
    /// @todo Construct a heap using the buildHeap algorithm

    // copy all elements
    _elems.push_back(T());
    for(size_t j = 0; j < elems.size(); j++){
      _elems.push_back(elems[j]);
    }


    for(size_t i = parent(_elems.size() - 1); i > 0; i--){
      heapifyDown(i);
    }

}

template <class T, class Compare>
T heap<T, Compare>::pop()
{
    /// @todo Remove, and return, the element with highest priority


    // store the return value and swap root with last element
    T ret = _elems[root()];
    _elems[root()] = _elems[_elems.size() - 1];

    // remove last element
    _elems.pop_back();

    heapifyDown(root());

    return ret;
}

template <class T, class Compare>
T heap<T, Compare>::peek() const
{
    /// @todo Return, but do not remove, the element with highest priority
    return _elems[1];
}

template <class T, class Compare>
void heap<T, Compare>::push(const T& elem)
{
    /// @todo Add elem to the heap

    // add to the back of elems and heapifyUp
    _elems.push_back(elem);
    heapifyUp(_elems.size() - 1);
}

template <class T, class Compare>
bool heap<T, Compare>::empty() const
{
    /// @todo Determine if the heap is empty
    return (_elems.size() == 1);
}

template <class T, class Compare>
void heap<T, Compare>::getElems(std::vector<T> & heaped) const
{
    for (size_t i = root(); i < _elems.size(); i++) {
        heaped.push_back(_elems[i]);
    }
}
