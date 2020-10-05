#include "graphNO.hpp"
#include "InstanceStable.hpp"
#include "mpi.h"

// Creation rapide d'une instance minimaliste pour tester
GraphNO createSmallExample() {
  GraphNO H = GraphNO(6);

  H.insertEdge(0, 1);
  H.insertEdge(1, 2);
  H.insertEdge(0, 2);
  H.insertEdge(0, 3);
  H.insertEdge(1, 3);
  H.insertEdge(2, 3);

  return H;
}

int main(int argc, char **argv) {
  MPI_Init(&argc, &argv);
  
  GraphNO G = createSmallExample();

  stableMax(G);

  MPI_Finalize();
  return 0;
}
