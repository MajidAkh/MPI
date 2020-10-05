#include <iostream>
#include <stdexcept>
#include <map>
#include "Isomorphism.hpp"
#include "mpi.h"
using namespace std;

// Exercice 3
void extendInjection(Mapping &m) {
  // The argument m is (a reference to) a partially-defined injective
  // function G -> H : it may only have images defined for a subset of G.
  // This procedure recursively attempts to extend m to the whole of G,
  // using a backtracking approach.

  if (m.isFull()) {
    // TODO : Completer ici
  }
  for (int nidg = 0; nidg < m.getSizeG(); nidg++) {
    // TODO : Completer ici
  }
  return;
}

void findIsomorphism(Graph G, Graph H) {
  if (G.vertexCount() != H.vertexCount()) {
    std::cout << "Pas d'isomorphisme" << std::endl;
    return;
  }
  Mapping candidate(G, H);
  extendInjection(candidate);
  if (candidate.isFull())
    std::cout << candidate << std::endl;
  else
    std::cout << "Pas d'isomorphisme" << std::endl;
}

// Exercice 4
void findSubIsomorphism(Graph G, Graph H) {
  // TODO : Completer ici

  // ...si aucun sous-isomorphisme trouve,
  std::cout << "Pas de sous-isomorphisme" << std::endl;
}

// Exercice 5
void findSubIsomorphismMPI(Graph G, Graph H) {
  int myrank, size;
  int n = H.vertexCount();

  MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  MPI_Status status;

  if (myrank == 0) {
    // TODO : Completer ici
  } else {
    // TODO : Completer ici
  }
  return;
}
