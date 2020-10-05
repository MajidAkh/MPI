#include <iostream>
#include <mpi.h>

int main (int argc, char *argv[]) {
    int id, p, r;
    MPI_Status status;
    MPI_Init(&argc, &argv); // Initialize MPI.
    MPI_Comm_size(MPI_COMM_WORLD, &p); // Get the number of processes.
    MPI_Comm_rank(MPI_COMM_WORLD, &id); // Get the individual process ID.
    // Print off a hello world message
    if(id%2 == 0){
        MPI_Send(&id,1,MPI_INT,id+1,0,MPI_COMM_WORLD);
    }else{
        MPI_Recv(&r,1,MPI_INT,id-1,0,MPI_COMM_WORLD,&status);
        std::cout << r+10*id << std::endl;
    }
    MPI_Finalize(); // Terminate MPI.
    return 0;
}