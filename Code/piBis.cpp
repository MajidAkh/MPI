#include <iostream>
#include <mpi.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>

int main (int argc, char *argv[]) {
    int id, p;
    unsigned long int n,pi,pi_loc = 0;
    MPI_Status status;
    MPI_Init(&argc, &argv); // Initialize MPI.
    MPI_Comm_size(MPI_COMM_WORLD, &p); // Get the number of processes.
    MPI_Comm_rank(MPI_COMM_WORLD, &id); // Get the individual process ID.
    // Print off a hello world message
    if (id == 0){
        std::cout
            << "Entrez le nombre de tirage (un entier > 1) :"
            << std::endl;
        std::cin >> n;   
    }
    MPI_Bcast(&n, 1, MPI_UNSIGNED_LONG, 0, MPI_COMM_WORLD);

    std::srand(id);
    std::srand(rand());
    for(unsigned long int i = 0; i < n; i++){
        pi_loc+=pow((float)rand()/(float)RAND_MAX,2)+pow((float)rand()/(float)RAND_MAX,2)<1;
    }
    MPI_Reduce (&pi_loc, &pi, 1, MPI_UNSIGNED_LONG, MPI_SUM, 0, MPI_COMM_WORLD);
    MPI_Bcast(&pi, 1, MPI_UNSIGNED_LONG, 0, MPI_COMM_WORLD);
    std::cout << "ID = " << id << " Pi_local = " << 4.0*(float)pi_loc/(float)n << " PI = "<< 4.0*(float)pi/(float)n/(float)p << std::endl;
    MPI_Finalize(); // Terminate MPI.
    return 0;
}