
#include <iterator>
#include <cmath>
#include <list>
#include <queue>

#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"
#include "BFS.h"

using namespace cs225;

/**
 * Initializes a breadth-first ImageTraversal on a given `png` image,
 * starting at `start`, and with a given `tolerance`.
 */
BFS::BFS(const PNG & png, const Point & start, double tolerance)
  :image_(png),visited(png.width(),std::vector<bool>(png.height(), false)) {
  /** @todo [Part 1] */
  start_ = start;
  tole_ = tolerance;
  toVisit.push(start);
}

/**
 * Returns an iterator for the traversal starting at the first point.
 */
ImageTraversal::Iterator BFS::begin() {
  /** @todo [Part 1] */
  BFS * trav_copy = new BFS(image_, start_, tole_);
  Point st = trav_copy->pop();
  return ImageTraversal::Iterator(trav_copy, st);
}

/**
 * Returns an iterator for the traversal one past the end of the traversal.
 */
ImageTraversal::Iterator BFS::end() {
  /** @todo [Part 1] */
  Point setinel(-1, -1); //set up a setinel node for end()
  return ImageTraversal::Iterator(new BFS(image_, start_, tole_), setinel);
}

/**
 * Adds a Point for the traversal to visit at some point in the future.
 */
void BFS::add(const Point & point) {
  /** @todo [Part 1] */

  // calculate delta
  double diff = calculateDelta(*image_.getPixel(start_.x, start_.y), *image_.getPixel(point.x, point.y));


  if(diff < tole_){
    toVisit.push(point);
  }

}

/**
 * Removes and returns the current Point in the traversal.
 */
Point BFS::pop() {
  /** @todo [Part 1] */


  Point next;

  //pop out next point to visit
  while(true){

    if(empty()){
      // if traveral is empty, return a setinel point
      Point next(-1, -1);
      return next;
    }


    // check if point has been visited
    next = toVisit.front();
    toVisit.pop();
    if(!visited[next.x][next.y]){
      // if the point is not visited, break the loop; otherwise, continue to pop out points
      break;
    }
  }

  // add element to the visited list
  visited[next.x][next.y] = true;

  // before returning, add this point's neighbor to the toVisit
  if(next.x < image_.width() - 1){
    // right neighbor
    Point pt1(next.x + 1, next.y);
    add(pt1);
  }

  if(next.y < image_.height() - 1){
    // below neighbor
    Point pt2(next.x, next.y + 1);
    add(pt2);
  }

  if(next.x > 0){
    // left neighbor
    Point pt3(next.x - 1, next.y);
    add(pt3);
  }


  if(next.y > 0){
    // above neighbor
    Point pt4(next.x, next.y - 1);
    add(pt4);
  }

  return next;
}

/**
 * Returns the current Point in the traversal.
 */
Point BFS::peek() const {
  /** @todo [Part 1] */
  return toVisit.front();
}

/**
 * Returns true if the traversal is empty.
 */
bool BFS::empty() const {
  /** @todo [Part 1] */
  return toVisit.empty();
}
