#ifndef GRAPHNO_H
#define GRAPHNO_H

#include <vector>
#include <set>

class GraphNO {
 public:
  // Constructor that creates a graph with numVertices vertices and no edges
  GraphNO(int numVertices)
      : n(numVertices),
        adjacencyList(std::vector<std::set<int> >(numVertices)){};

  // returns the number of vertices in the graph
  int vertexCount() { return n; };

  // return the number of neighbors of the vertex nid
  int neighborCount(int nid) { return adjacencyList[nid].size(); }

  // return the number of neighbors of the vertex nid
 // int minIndex(int nid) { return adjacencyList[nid].size(); }

  // inserts an edge between nidFrom and nidTo
  void insertEdge(int nidFrom, int nidTo);

  // remove an edge between nidFrom and nidTo
  void removeEdge(int nidFrom, int nidTo);
  
  // returns true if and only if there is an edge between nidFrom and nidTo
  bool isEdge(int nidFrom, int nidTo) {
    return adjacencyList[nidTo].count(nidFrom) != 0;
  }

  // Get Neighbors
  std::set<int> *  getNeighbors(int nid) {return *(adjacencyList[nid]);}


 private:
  // number of vertices in the graph
  int n;

  // adjacency lists for neighbors of the vertices
  std::vector<std::set<int> > adjacencyList;
};

#endif
