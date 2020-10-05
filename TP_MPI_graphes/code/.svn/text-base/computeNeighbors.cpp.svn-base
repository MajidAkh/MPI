#include <iostream>
#include <vector>

// messages are received from node with highest 1-bit flipped to 0
int computePredecessor(int node) {
  // TODO
  return -1;
}

// compute neighbors to communicate to
std::vector<int> computeOutNeighbors(int node, int numberNodes) {
  std::vector<int> neighbors;

  // first bit to flip
  int flipbit = (node - computePredecessor(node)) * 2;

  // TODO

  return neighbors;
}

// print neighbor list for debugging
void printNeighbors(std::vector<int> neighbors) {
  for (std::vector<int>::iterator iter = neighbors.begin();
       iter != neighbors.end(); iter++) {
    std::cout << *iter << " ";
  }
  std::cout << std::endl;
}
