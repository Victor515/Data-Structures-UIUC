#include "maze.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <stack>

using std::rand;
using std::srand;
using std::vector;
using std::make_pair;

void SquareMaze::makeMaze (int width, int height){
  maze_ = vector< vector<square>>(width, vector<square>(height));
  dset.addelements(width * height);
  width_ = width;
  height_ = height;

  int x, y, dir;
  int numWall = 0;
  while(numWall < width * height - 1){
    x = rand() % width;
    y = rand() % height;
    dir = rand() % 2; // either 0 or 1

    // check whether we can delete the wall or not; if not, randomly pick again
    if(x == width - 1 && dir == 0){
      // cannot delete right wall
      continue;
    }

    if(y == height - 1 && dir == 1){
      // cannot delete bottom wall
      continue;
    }

    // try to delete right wall
    if(dir == 0){
      int right_x = x + 1;
      int index_left = y * width + x;
      int index_right = index_left + 1;
      if(dset.find(index_left) == dset.find(index_right)){
        continue;
      }

      else{
        setWall(x, y ,dir, false);
        numWall++; // increase counter by 1
        dset.setunion(index_left, index_right); // union two sets
      }
    }

    if(dir == 1){
      int down_y = y + 1;
      int index_up = y * width + x;
      int index_down = down_y * width + x;
      if(dset.find(index_up) == dset.find(index_down)){
        continue;
      }

      else{
        setWall(x, y, dir, false);
        numWall++;
        dset.setunion(index_up, index_down);
      }
    }
  }

}

bool SquareMaze::canTravel (int x, int y, int dir) const {
  // check boundary
  if(x == width_ - 1 && dir == 0){
    return false;
  }
  if(x == 0 && dir == 2){
    return false;
  }
  if(y == height_ - 1 && dir == 1){
    return false;
  }
  if(y == 0 && dir == 3){
    return false;
  }

  if(dir == 0){
    return !maze_[x][y].right;
  }
  if(dir == 1){
    return !maze_[x][y].down;
  }
  if(dir == 2){
    return !maze_[x - 1][y].right;
  }
  if(dir == 3){
    return !maze_[x][y - 1].down;
  }
  else{
    return false;
  }
}

void SquareMaze::setWall (int x, int y, int dir, bool exists){
  if(dir == 0){
      maze_[x][y].right = exists;
  }

  if(dir == 1){
    maze_[x][y].down = exists;
  }
}

vector<int> SquareMaze::solveMaze (){
  std::unordered_map<int, vector<int>> fromOrigin; // store path from the origin to the point
  size_t curr_max = 0;
  vector<int> ret;
  // iterate through every square at the bottom
  for(int i = 0; i < width_; i++){
    int x = i;
    int y = height_ - 1;
    vector<vector<bool> > visited;
  	for (int i = 0; i < width_; i++)
  		visited.push_back(vector<bool>(height_));
    //bool found = false;
    //unordered_set<int> visited;
    vector<int> path = dfs1(x, y, visited, fromOrigin);
    //int p = x + y * width_;
    //toOrigin[p] = path;
    if(path.size() > curr_max){
      ret = path;
      curr_max = path.size();
    }
  }

  // // find the maximum distance path and reverse the result
  // size_t curr_max = 0;
  // vector<int> ret;
  // for(int k = 0; k < width_; k++){
  //   int x = k;
  //   int y = height_ - 1;
  //   int p = x + y * width_;
  //   vector<int> temp = toOrigin[p];
  //   if(temp.size() > curr_max){
  //     ret = temp;
  //     curr_max = temp.size();
  //   }
  // }
  //std::reverse(ret.begin(), ret.end());
  return ret;
}

PNG * SquareMaze::drawMaze () const{
  PNG * pic = new PNG(width_ * 10 + 1, height_ * 10 + 1);
  for(unsigned int i = 0; i < pic->width(); i++){
    if(i >= 1 && i <= 9){
      continue;
    }
    // set to black color
    pic->getPixel(i, 0)->h = 0;
    pic->getPixel(i, 0)->l = 0;
    pic->getPixel(i, 0)->s = 0;
    pic->getPixel(i, 0)->a = 1;
  }

  for(unsigned int j = 0; j < pic->height(); j++){
    pic->getPixel(0, j)->h = 0;
    pic->getPixel(0, j)->l = 0;
    pic->getPixel(0, j)->s = 0;
    pic->getPixel(0, j)->a = 1;
  }

  for(int x = 0; x < width_; x++){
    for(int y = 0; y < height_; y++){
      // if right wall exists
      if(maze_[x][y].right){
        for(int k = 0; k <= 10; k++){
          pic->getPixel((x + 1) * 10, y * 10 + k)->h = 0;
          pic->getPixel((x + 1) * 10, y * 10 + k)->l = 0;
          pic->getPixel((x + 1) * 10, y * 10 + k)->s = 0;
          pic->getPixel((x + 1) * 10, y * 10 + k)->a = 1;
        }
      }

      if(maze_[x][y].down){
        for(int k = 0; k <= 10; k++){
          pic->getPixel(x * 10 + k, (y + 1)* 10)->h = 0;
          pic->getPixel(x * 10 + k, (y + 1)* 10)->l = 0;
          pic->getPixel(x * 10 + k, (y + 1)* 10)->s = 0;
          pic->getPixel(x * 10 + k, (y + 1)* 10)->a = 1;
        }
      }
    }
  }

  return pic;
}

PNG * SquareMaze::drawMazeWithSolution (){
  PNG * pic = drawMaze();
  vector<int> path = solveMaze();
  unsigned int x = 5;
  unsigned int y = 5;
  int coorX = 0;
  int coorY = 0;
  for(size_t i = 0; i < path.size(); i++){
    // right
    if(path[i] == 0){
      for(unsigned int k = 0; k <= 10; k++){
        pic->getPixel(x + k, y)->h = 0;
        pic->getPixel(x + k, y)->l = 0.5;
        pic->getPixel(x + k, y)->s = 1;
        pic->getPixel(x + k, y)->a = 1;
      }
      x += 10;
      coorX += 1;
    }

    // down
    if(path[i] == 1){
      for(unsigned int k = 0; k <= 10; k++){
        pic->getPixel(x, y + k)->h = 0;
        pic->getPixel(x, y + k)->l = 0.5;
        pic->getPixel(x, y + k)->s = 1;
        pic->getPixel(x, y + k)->a = 1;
      }
      y += 10;
      coorY += 1;
    }

    // left
    if(path[i] == 2){
      for(unsigned int k = 0; k <= 10; k++){
        pic->getPixel(x - k, y)->h = 0;
        pic->getPixel(x - k, y)->l = 0.5;
        pic->getPixel(x - k, y)->s = 1;
        pic->getPixel(x - k, y)->a = 1;
      }
      x -= 10;
      coorX -= 1;
    }

    // up
    if(path[i] == 3){
      for(unsigned int k = 0; k <= 10; k++){
        pic->getPixel(x, y - k)->h = 0;
        pic->getPixel(x, y - k)->l = 0.5;
        pic->getPixel(x, y - k)->s = 1;
        pic->getPixel(x, y - k)->a = 1;
      }
      y -= 10;
      coorY -= 1;
    }
  }
  // make the exit
  for(int n = 1; n <= 9; n++){
    pic->getPixel(coorX * 10 + n, (coorY + 1) * 10)->h = 0;
    pic->getPixel(coorX * 10 + n, (coorY + 1) * 10)->l = 1;
    pic->getPixel(coorX * 10 + n, (coorY + 1) * 10)->s = 0;
    pic->getPixel(coorX * 10 + n, (coorY + 1) * 10)->a = 1;
  }
  return pic;
}

void SquareMaze::dfs(int x, int y, vector<int> & path, std::unordered_map<int, vector<int>> & toOrigin, bool & found, unordered_set<int> visited){
  if(x == 0 && y == 0){
    // when we find the origin
    found = true;
    return;
  }

  int temp_pair = x + y * width_;
  visited.insert(temp_pair);
  // if there is a searched path from current (x, y) to the origin
  if(toOrigin.find(temp_pair) != toOrigin.end()){
    auto searched_path = toOrigin[temp_pair];
    path.insert(path.begin(), searched_path.begin(), searched_path.end());
    found = true;
    return;
  }

  // go left(store right)
  if(canTravel(x, y, 2)){
    // check if left has been visited
    int left_point = y * width_ + x - 1;
    if(visited.find(left_point) == visited.end()){
      dfs(x - 1, y, path, toOrigin, found,visited);
    }
    if(found){
      path.insert(path.begin(), 0);
      toOrigin[temp_pair] = path;
      return;
    }
  }
  // go right
  if(canTravel(x, y, 0)){
    int right_point = y * width_ + x + 1;
    if(visited.find(right_point) == visited.end()){
      dfs(x + 1, y, path, toOrigin, found, visited);
    }
    if(found){
      path.insert(path.begin(), 2);
      toOrigin[temp_pair] = path;
      return;
    }
  }

  // go up
  if(canTravel(x, y, 3)){
    int up_point = x + width_ * (y - 1);
    if(visited.find(up_point) == visited.end()){
      dfs(x, y - 1, path, toOrigin, found, visited);
    }
    if(found){
      path.insert(path.begin(), 1);
      toOrigin[temp_pair] = path;
      return;
    }
  }

  // go down
  if(canTravel(x, y, 1)){
    int down_point = x + width_ * (y + 1);
    if(visited.find(down_point) == visited.end()){
      dfs(x, y + 1, path, toOrigin, found, visited);
    }
    if(found){
      path.insert(path.begin(), 3);
      toOrigin[temp_pair] = path;
      return;
    }
  }
}

vector<int> SquareMaze::dfs1(int x_, int y_, vector<vector <bool>> & visited, std::unordered_map<int, vector<int>> & fromOrigin){
  unordered_map<int, int> parent;
  std::stack<std::pair<int, int>> s;
  s.push(make_pair(x_, y_));

  int x, y;
  while(!s.empty()){
    x = s.top().first;
    y = s.top().second;
    //std::cout << "x: " << x << "y: "<< y << std::endl;
    s.pop();
    if(x == 0 && y == 0){
      break;
    }
    // if the point has been searched
    if(fromOrigin.find(x + y * width_) != fromOrigin.end()){
      break;
    }
    visited[x][y] = true; // if not, set visited

    if(canTravel(x, y, 0) && !visited[x + 1][y]){
        s.push(make_pair(x+1, y));
        parent[x + 1 + y * width_] = 2; // save path to the parent
      }
    if(canTravel(x, y, 1) && !visited[x][y + 1]){
        s.push(make_pair(x, y+1));
        parent[x + (y + 1) * width_] = 3;
      }
    if(canTravel(x, y, 2) && !visited[x - 1][y]){
      s.push(make_pair(x-1, y));
      parent[x - 1 + y * width_] = 0;
    }
    if(canTravel(x, y, 3) && !visited[x][y - 1]){
        s.push(make_pair(x, y-1));
        parent[x + (y - 1) * width_] = 1;
      }
    // std::cout << parent[4] << std::endl;
  }

  int curr = x + y * width_; // from origin or the point whose path from orgin is known, reconstruct the path

  vector<int> path = fromOrigin[curr];
  while(curr != x_ + y_ * width_){
     //std::cout << "curr: " << curr << std::endl;
    path.push_back(parent[curr]);
    if(parent[curr] == 0){
      //std::cout << "right" << std::endl;
      curr += 1;
      fromOrigin[curr] = path;
      continue;
    }
    if(parent[curr] == 1){
      //std::cout << "down" << std::endl;
      curr += width_;
      fromOrigin[curr] = path;
      continue;
    }
    if(parent[curr] == 2){
      //std::cout << "left" << std::endl;
      curr -= 1;
      fromOrigin[curr] = path;
      continue;
    }
    if(parent[curr] == 3){
      //std::cout << "up" << std::endl;
      curr -= width_;
      fromOrigin[curr] = path;
      continue;
    }
  }

  return path;
}
