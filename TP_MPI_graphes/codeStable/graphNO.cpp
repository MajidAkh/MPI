
#include "graphNO.hpp"

void GraphNO::insertEdge(int nidFrom, int nidTo) {
  //    std::cout << "ajout de " << nidFrom << " a " << nidTo << std::endl;
  adjacencyList[nidTo].insert(nidFrom);
  adjacencyList[nidFrom].insert(nidTo);
}

void GraphNO::removeEdge(int nidFrom, int nidTo) {
    adjacencyList[nidTo].erase (nidFrom);
    adjacencyList[nidFrom].erase (nidTo);
}

/*
void GraphNO::maxIndex(int nidFrom) {
    // Get the maximum element 
    int max_element; 
    if (!my_set.empty()) 
        max_element = *my_set.end(); 
  
    // return the maximum element 
    return max_element; 
}*/
