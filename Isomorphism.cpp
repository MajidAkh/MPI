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
    return;
  }
  for (int nidg = 0; nidg < m.getSizeG(); nidg++) {
    for (int njdh = 0; njdh < m.getSizeH(); njdh++) {
      if(m.areMappable(nidg,njdh)){
        m.addToMap(nidg,njdh);
        extendInjection(m);
        if (m.isFull()) {
          return;
        }
        m.deleteFromMap(nidg);
      }
    }
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
  Mapping candidate(G, H);
  extendInjection(candidate);
  if (candidate.isFull())
    std::cout << candidate << std::endl;
  else
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
    int indice = 0, garb, end = -1,flag;
    int cpp = size-1;
    MPI_Request reqs[size-1];
    for(int i = 1; i<size;i++){
      MPI_Irecv (&garb, 1, MPI_INT, i, 0, MPI_COMM_WORLD, &reqs[i]);
    }
    while(indice <  H.vertexCount()){
      for(int i = 1; i<size;i++){
          MPI_Test(&reqs[i],&flag,&status);
          if(flag){
            if(indice < H.vertexCount()){
              MPI_Isend(&indice, 1, MPI_INT, i, 0, MPI_COMM_WORLD, &reqs[0]);
              indice++;
              MPI_Irecv (&garb, 1, MPI_INT, i, 0, MPI_COMM_WORLD, &reqs[i]);
              if(garb == 1){
                break;
              }
            }
          }
      }
    }
    for(int i = 1; i<size;i++){
      MPI_Isend(&end, 1, MPI_INT, i, 0, MPI_COMM_WORLD, &reqs[0]);
    }
  } else {
    MPI_Request reqs[2];
    int indice = 0;
    int end = 0;
    while(true){
      MPI_Isend(&end, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &reqs[0]);
      MPI_Irecv (&indice, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &reqs[1]);
      MPI_Wait (&reqs[1], &status);
      cerr << myrank << " "<< indice << endl;
      if(indice == -1){
        break;
      }
      Mapping candidate(G, H);
      candidate.addToMap(0,indice);
      extendInjection(candidate);
      if (candidate.isFull()){
        std::cout << candidate << std::endl;
        end = 1;
      }else
        std::cout << "Pas de sous-isomorphisme" << std::endl;
      
    }

  }
  return;
}
