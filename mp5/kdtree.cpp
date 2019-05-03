/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */
template <int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim>& first,
                                const Point<Dim>& second, int curDim) const
{
    /**
     * @todo Implement this function!
     */
    if(first[curDim] != second[curDim]){
      return first[curDim] < second[curDim];
    }

    else{
      // if there is a tie
        return first < second;
    }
}

template <int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim>& target,
                                const Point<Dim>& currentBest,
                                const Point<Dim>& potential) const
{
    /**
     * @todo Implement this function!
     */
    double currdiff = 0;
    double potdiff = 0;

    for(unsigned i = 0; i < Dim; i++){
      currdiff += (target[i] - currentBest[i]) * (target[i] - currentBest[i]);
      potdiff  += (target[i] - potential[i]) * (target[i] - potential[i]);
    }

    if(currdiff != potdiff){
      return potdiff < currdiff;
    }

    else{
      // if there is tie
      return potential < currentBest;
    }
}

template <int Dim>
KDTree<Dim>::KDTree(const vector<Point<Dim>>& newPoints)
{
    /**
     * @todo Implement this function!
     */
    // Copy all points by value
    points = newPoints;

    construct(points, 0, points.size() - 1, 0);
}


template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query) const
{
    /**
     * @todo Implement this function!
     */

    return findNearestNeighbor(query, 0, points.size() - 1, 0);
}

template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query, int left, int right, int order) const
{
    /**
     * @todo Implement this function!
     */

     // if reach a leaf node
     if(left >= right){
       return points[left];
     }

     // find the node in current level
     int median = (left + right) / 2;
     Point<Dim> currentBest;

     // traverse down the tree
     bool goLeft = smallerDimVal(query, points[median], order); // track which halves we traverse
     if(goLeft){
       currentBest = findNearestNeighbor(query, left, median - 1, (order + 1) % Dim);
     }

     else{
       currentBest = findNearestNeighbor(query, median + 1, right, (order + 1) % Dim);
     }

     // back traversal phase
     // step 1 check if currentBest should be replaced by parent node
     if(shouldReplace(query, currentBest, points[median])){
       currentBest = points[median];
     }

     // step 2 determine if we need to traverse the other part of tree
     int radius = 0;
     for(unsigned i = 0; i < Dim; i++){
       radius += (query[i] - currentBest[i]) * (query[i] - currentBest[i]);
     }

     int planeDistance = (query[order] - points[median][order]) * (query[order] - points[median][order]);

     // if we do need
     if(planeDistance <= radius){ // note the equal sign is essential
       Point<Dim> otherBest;

       if(goLeft){
         otherBest = findNearestNeighbor(query, median + 1, right, (order + 1) % Dim);
       }
       else{
         otherBest = findNearestNeighbor(query, left, median - 1, (order + 1) % Dim);
       }

       if(shouldReplace(query, currentBest, otherBest)){
         currentBest = otherBest;
       }
     }


    return currentBest;
}



template <int Dim>
void KDTree<Dim>::construct(vector<Point<Dim>> & points, int a, int b, int order){

  // there is chance left index is greater than right index for base case
  if(a >= b){
    return;
  }

  int median = (a + b) / 2;
  quickSelect(points, a, b, median, order);

  construct(points, a, median - 1, (order + 1) % Dim);
  construct(points, median + 1, b, (order + 1) % Dim);
}

template <int Dim>
void KDTree<Dim>::quickSelect(vector<Point<Dim>> & points, int a, int b, int k, int order){

  // Just to keep the same as quicksort, actually there is no chance a > b
  if(a >= b){
    return;
  }

  // randomly generate an index (take a guess)
  //std::cout<<"a before: "<<a<<std::endl;
  //std::cout<<"b before: "<<b<<std::endl;
  int pivotindex = a + (std::rand() % (b - a + 1));
  //std::cout<<"pivotindex picked: "<<pivotindex<<std::endl;

  pivotindex = partition(points, a, b, pivotindex, order);
  //std::cout<<"pivotindex final position: "<<pivotindex<<std::endl;
  //std::cout<<"a after: "<<a<<std::endl;
  //std::cout<<"b after: "<<b<<std::endl;
  //std::cout<<"k: "<<k<<std::endl;
  //std::cout<<"last element: "<<points[b][order]<<std::endl;

  if(k == pivotindex){
    return;
  }
  else if(k < pivotindex){
    quickSelect(points, a, pivotindex - 1, k, order);
    return;
  }
  else{
    quickSelect(points, pivotindex + 1, b, k, order);
    return;
  }

}

template <int Dim>
int KDTree<Dim>::partition(vector<Point<Dim>> & points, int a, int b, int pivotindex, int order){
  //std::cout<<"order: "<<order<<std::endl;
  int pivotValue = points[pivotindex][order];

  // need to implement swap
  Point<Dim> temp = points[pivotindex]; // store pivot in temp
  points[pivotindex] = points[b]; // store right point at pivot index
  points[b] = temp;

  int storeIndex = a;

  // move elements
  for(int i = a; i < b; i++){
    //std::cout<<"storeIndex : "<<storeIndex<<std::endl;
    if(points[i][order] == pivotValue){
      // if there is a tie, use Point class's operator <
      // right now pivot point is at index b
      if(points[i] < points[b]){
        Point<Dim> temp = points[i];
        points[i] = points[storeIndex];
        points[storeIndex] = temp;
        storeIndex++;
        //std::cout<<"I have been here 1"<<std::endl;
      }
    }

    else if(points[i][order] < pivotValue){
      Point<Dim> temp = points[i];
      points[i] = points[storeIndex];
      points[storeIndex] = temp;
      storeIndex++;
      //std::cout<<"I have been here 2"<<std::endl;
    }
  }

  // Swap points[b] and points[storeIndex]
  temp = points[storeIndex];
  points[storeIndex] = points[b];
  points[b] = temp;
  return storeIndex;
}
