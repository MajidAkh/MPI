#include <iostream>
#include <vector>
#include <math.h>

// messages are received from node with highest 1-bit flipped to 0
int computePredecessor(int node) {
  return node - pow(2,floor(log2(node)));
}

// compute neighbors to communicate to
std::vector<int> computeOutNeighbors(int node, int numberNodes) {
  std::vector<int> neighbors;
  // first bit to flip
  int flipbit = std::max(1,(node - computePredecessor(node)) * 2);
  while(node+flipbit < numberNodes){
    neighbors.push_back(node+flipbit);
    flipbit*=2;
  }
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
