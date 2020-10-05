#include <vector>

#include "mpi.h"
#include "computeNeighbors.hpp"

void broadcast() {
  const int root = 0;
  int myrank, size;
  MPI_Status status;

  MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  int round = 0;
  int tag = 0;

  // root does not have to wait for a message
  if (myrank != root) {
    // wait for message from predecessor and print out the round
    int pred = 0;
    // TODO
    std::cout << "node " << myrank << " received message from " << pred
              << " in round " << round << std::endl;
  }

  // now let's send

  // first compute neighbors to send to
  // TODO

  // iterate over neighbors and send
  // TODO

}

int main(int argc, char *argv[]) {
  MPI_Init(&argc, &argv);
  broadcast();
  MPI_Finalize();
  return 0;
}
