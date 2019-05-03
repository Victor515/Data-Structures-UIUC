#ifndef MAZE_H
#define MAZE_H

#include "dsets.h"
#include "cs225/PNG.h"
#include <vector>
#include <unordered_map>
#include <unordered_set>

using std::vector;
using std::unordered_map;
using std::unordered_set;
using namespace cs225;

class SquareMaze{
  private:
    struct square{
      bool down;
      bool right;
      square():down(true),right(true){} // initialize square
    };
  public:
   	void makeMaze (int width, int height);
    bool canTravel (int x, int y, int dir) const ;
    void setWall (int x, int y, int dir, bool exists);
    vector<int> solveMaze ();
    PNG * drawMaze () const;
    PNG * drawMazeWithSolution ();
    void dfs(int x, int y, vector<int> & path, unordered_map<int, vector<int>> & toOrigin, bool & found, unordered_set<int> visited);
    vector<int> dfs1(int x, int y, vector<vector <bool>> & visited, unordered_map<int, vector<int>> & fromOrigin);
  private:
    vector< vector<square>> maze_;
    DisjointSets dset;
    int width_;
    int height_;
};

#endif
