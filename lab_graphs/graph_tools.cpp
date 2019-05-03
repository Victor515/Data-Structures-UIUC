/**
 * @file graph_tools.cpp
 * This is where you will implement several functions that operate on graphs.
 * Be sure to thoroughly read the comments above each function, as they give
 *  hints and instructions on how to solve the problems.
 */

#include "graph_tools.h"

/**
 * Finds the minimum edge weight in the Graph graph.
 * THIS FUNCTION IS GRADED.
 *
 * @param graph - the graph to search
 * @return the minimum weighted edge
 *
 * @todo Label the minimum edge as "MIN". It will appear blue when
 *  graph.savePNG() is called in minweight_test.
 *
 * @note You must do a traversal.
 * @note You may use the STL stack and queue.
 * @note You may assume the graph is connected.
 *
 * @hint Initially label vertices and edges as unvisited.
 */
int GraphTools::findMinWeight(Graph& graph)
{
  // set up the graph
  for(auto v : graph.getVertices()){
    graph.setVertexLabel(v, "UNEXPLORED");
  }
  for(auto e : graph.getEdges()){
    graph.setEdgeLabel(e.source, e.dest, "UNEXPLORED" );
  }

  int minWeight = INT_MAX;
  Edge minEdge;
  // BST traversal
  for(auto v : graph.getVertices()){

    if(graph.getVertexLabel(v) == "UNEXPLORED"){
      queue<Vertex> q;
      Vertex curr;
      graph.setVertexLabel(v, "VISITED");
      q.push(v);

      while(!q.empty()){

        curr = q.front();
        q.pop();
        // iterate through adjacent vertex of curr
        for(auto w : graph.getAdjacent(curr)){

          if(graph.getVertexLabel(w) == "UNEXPLORED"){
            graph.setVertexLabel(w, "VISITED");
            graph.setEdgeLabel(curr, w, "DISCOVERY");
            q.push(w);
            // compare edge weight with current global min weight
            if(graph.getEdgeWeight(curr, w) < minWeight){
              minWeight = graph.getEdgeWeight(curr,w);
              minEdge.source = curr;
              minEdge.dest = w;
            }
          }

          else if(graph.getEdgeLabel(curr, w) == "UNEXPLORED"){
            if(graph.getEdgeWeight(curr, w) < minWeight){
              minWeight = graph.getEdgeWeight(curr, w);
              minEdge.source = curr;
              minEdge.dest = w;
            }
            graph.setEdgeLabel(curr, w, "CROSS");
          }

        }
      }
    }
  }

  graph.setEdgeLabel(minEdge.source, minEdge.dest, "MIN");
  return minWeight;
}

/**
 * Returns the shortest distance (in edges) between the Vertices
 *  start and end.to test on a random graph with 8 vertices and random seed 47.
int GraphTools::findShortestPath(Graph &
 * THIS FUNCTION IS GRADED.
 *
 * @param graph - the graph to search
 * @param start - the vertex to start the search from
 * @param end - the vertex to find a path to
 * @return the minimum number of edges between start and end
 *
 * @todo Label each edge "MINPATH" if it is part of the minimum path
 *
 * @note Remember this is the shortest path in terms of edges,
 *  not edge weights.
 * @note Again, you may use the STL stack and queue.
 * @note You may also use the STL's unordered_map, but it is possible
 *  to solve this problem without it.
 *
 * @hint In order to draw (and correctly count) the edges between two
 *  vertices, you'll have to remember each vertex's parent somehow.
 */
int GraphTools::findShortestPath(Graph& graph, Vertex start, Vertex end)
{
    // set up the graph
    for(auto v : graph.getVertices()){
      graph.setVertexLabel(v, "UNEXPLORED");
    }
    for(auto e : graph.getEdges()){
      graph.setEdgeLabel(e.source, e.dest, "UNEXPLORED" );
    }

    // BST traversal
    queue<Vertex> q;
    Vertex curr;
    graph.setVertexLabel(start, "VISITED");
    q.push(start);
    std::unordered_map<Vertex, Vertex> parent; // to reconstrcut path
    int minNumEdges = 0;

    while(!q.empty()){
      // do traversal by level order(actually there is no need for this)
      for(size_t i = 0; i < q.size(); i++){
        curr = q.front();
        q.pop();
        // iterate through adjacent vertex of curr
        for(auto w : graph.getAdjacent(curr)){

          if(graph.getVertexLabel(w) == "UNEXPLORED"){
            graph.setVertexLabel(w, "VISITED");
            graph.setEdgeLabel(curr, w, "DISCOVERY");
            q.push(w);
            parent[w] = curr; // set the parent
          }

          else if(graph.getEdgeLabel(curr, w) == "UNEXPLORED"){
            graph.setEdgeLabel(curr, w, "CROSS");
          }
        }
      }
    }

    Vertex back = end;
    while(back != start){
      graph.setEdgeLabel(back, parent[back], "MINPATH");
      back = parent[back];
      minNumEdges++;
    }
    return minNumEdges;
}

/**
 * Finds a minimal spanning tree on a graph.
 * THIS FUNCTION IS GRADED.
 *
 * @param graph - the graph to find the MST of
 *
 * @todo Label the edges of a minimal spanning tree as "MST"
 *  in the graph. They will appear blue when graph.savePNG() is called.
 *
 * @note Use your disjoint sets class from MP 7.1 to help you with
 *  Kruskal's algorithm. Copy the files into the libdsets folder.
 * @note You may call std::sort instead of creating a priority queue.
 */
void GraphTools::findMST(Graph& graph)
{
    std::unordered_map<Vertex, int> vertexToNum; // map vertex to their index in DisjointSet
    DisjointSets dset;
    int index = 0;
    for(auto v : graph.getVertices()){
      vertexToNum[v] = index;
      index++;
    }
    dset.addelements(index + 1);

    vector<Edge> edgeList = graph.getEdges();
    // sort the edgelist
    std::sort(edgeList.begin(), edgeList.end(), [](Edge a, Edge b){
      return a < b;
    });

    size_t numEdges = 0;
    for(size_t i = 0; i < edgeList.size(); i++){
      Edge e = edgeList[i];
      Vertex source = e.source;
      Vertex dest = e.dest;
      int sourceIndex = vertexToNum[source];
      int destIndex = vertexToNum[dest];

      // if the edge connect two different sets
      if(dset.find(sourceIndex) != dset.find(destIndex)){
        graph.setEdgeLabel(source, dest, "MST");
        numEdges++;
        dset.setunion(dset.find(sourceIndex), dset.find(destIndex));
      }

      if(numEdges == graph.getVertices().size() - 1){
        break;
      }
    }
}
