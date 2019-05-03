/**
 * @file NimLearner.cpp
 * CS 225 - Fall 2017
 */

#include "NimLearner.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

using std::string;
using std::vector;

/**
 * Constructor to create a game of Nim with `startingTokens` starting tokens.
 *
 * This function creates a graph, `g_` representing all of the states of a
 * game of Nim with vertex labels "p#-X", where:
 * - # is the current player's turn; p1 for Player 1, p2 for Player2
 * - X is the tokens remaining at the start of a player's turn
 *
 * For example:
 *   "p1-4" is Player 1's turn with four (4) tokens remaining
 *   "p2-8" is Player 2's turn with eight (8) tokens remaining
 *
 * All legal moves between states are created as edges with initial weights
 * of 0.
 *
 * @param startingTokens The number of starting tokens in the game of Nim.
 */
NimLearner::NimLearner(unsigned startingTokens) : g_(true) {

  // seed the random number generator
  std::srand(std::time(0));

  // insert all vertices with correct labels
  for(unsigned i = 0; i <= startingTokens; i++){
    string label1 = "p1-" + std::to_string(i);
    string label2 = "p2-" + std::to_string(i);
    g_.insertVertex(label1);
    g_.insertVertex(label2);
  }

  // add all edges with weight = 0
  for(unsigned j = 0; j < startingTokens; j++){
    // special case for the second last vertex
    if(j == startingTokens - 1){
      // construct the label
      string label1_0 = "p1-" + std::to_string(j);
      string label1_1 = "p2-" + std::to_string(j + 1);

      string label2_0 = "p2-" + std::to_string(j);
      string label2_1 = "p1-" + std::to_string(j + 1);

      // add edges
      g_.insertEdge(g_.getVertexByLabel(label1_1), g_.getVertexByLabel(label1_0));
      g_.setEdgeWeight(g_.getVertexByLabel(label1_1), g_.getVertexByLabel(label1_0), 0);

      g_.insertEdge(g_.getVertexByLabel(label2_1), g_.getVertexByLabel(label2_0));
      g_.setEdgeWeight(g_.getVertexByLabel(label2_1), g_.getVertexByLabel(label2_0), 0);
    }

    else{
      string label1_0 = "p1-" + std::to_string(j);
      string label1_1 = "p2-" + std::to_string(j + 1);
      string label1_2 = "p2-" + std::to_string(j + 2);

      string label2_0 = "p2-" + std::to_string(j);
      string label2_1 = "p1-" + std::to_string(j + 1);
      string label2_2 = "p1-" + std::to_string(j + 2);

      // add edges and change weight to 0 (Default -1)
      g_.insertEdge(g_.getVertexByLabel(label1_1), g_.getVertexByLabel(label1_0));
      g_.setEdgeWeight(g_.getVertexByLabel(label1_1), g_.getVertexByLabel(label1_0), 0);

      g_.insertEdge(g_.getVertexByLabel(label1_2), g_.getVertexByLabel(label1_0));
      g_.setEdgeWeight(g_.getVertexByLabel(label1_2), g_.getVertexByLabel(label1_0), 0);

      g_.insertEdge(g_.getVertexByLabel(label2_1), g_.getVertexByLabel(label2_0));
      g_.setEdgeWeight(g_.getVertexByLabel(label2_1), g_.getVertexByLabel(label2_0), 0);

      g_.insertEdge(g_.getVertexByLabel(label2_2), g_.getVertexByLabel(label2_0));
      g_.setEdgeWeight(g_.getVertexByLabel(label2_2), g_.getVertexByLabel(label2_0), 0);
    }
  }

  startingVertex_ = g_.getVertexByLabel("p1-" + std::to_string(startingTokens));
}

/**
 * Plays a random game of Nim, returning the path through the state graph
 * as a vector of `Edge` classes.  The `origin` of the first `Edge` must be
 * the vertex with the label "p1-#", where # is the number of starting
 * tokens.  (For example, in a 10 token game, result[0].origin must be the
 * vertex "p1-10".)
 *
 * @returns A random path through the state space graph.
 */
std::vector<Edge> NimLearner::playRandomGame() const {
  vector<Edge> path;
  Vertex curr = startingVertex_;
  while(true){
    vector<Vertex> adjacent = g_.getAdjacent(curr); // find the next steps we could choose
    int pick = std::rand() % adjacent.size();
    Vertex next = adjacent[pick];
    Edge e = g_.getEdge(curr, next);
    path.push_back(e);

    curr = next;
    if(g_.getVertexLabel(curr) == "p1-0" || g_.getVertexLabel(curr) == "p2-0"){
      break;
    }
  }

  return path;
}


/*
 * Updates the edge weights on the graph based on a path through the state
 * tree.
 *
 * If the `path` has Player 1 winning (eg: the last vertex in the path goes
 * to Player 2 with no tokens remaining, or "p2-0", meaning that Player 1
 * took the last token), then all choices made by Player 1 (edges where
 * Player 1 is the source vertex) are rewarded by increasing the edge weight
 * by 1 and all choices made by Player 2 are punished by changing the edge
 * weight by -1.
 *
 * Likewise, if the `path` has Player 2 winning, Player 2 choices are
 * rewarded and Player 1 choices are punished.
 *
 * @param path A path through the a game of Nim to learn.
 */
void NimLearner::updateEdgeWeights(const std::vector<Edge> & path) {
  // if player one loses
  if(g_.getVertexLabel(path[path.size() - 1].dest) == "p1-0"){
    int weight_change = -1;
    for(Edge e : path){
      int weight = g_.getEdgeWeight(e.source, e.dest) + weight_change;
      g_.setEdgeWeight(e.source, e.dest, weight);
      weight_change *= -1;
    }
  }

  // if player one wins
  if(g_.getVertexLabel(path[path.size() - 1].dest) == "p2-0"){
    int weight_change = 1;
    for(Edge e : path){
      int weight = g_.getEdgeWeight(e.source, e.dest) + weight_change;
      g_.setEdgeWeight(e.source, e.dest, weight);
      weight_change *= -1;
    }
  }
}


/**
 * Returns a constant reference to the state space graph.
 *
 * @returns A constant reference to the state space graph.
 */
const Graph & NimLearner::getGraph() const {
  return g_;
}
