#include <iostream>
#include <mpi.h>

int main (int argc, char *argv[]) {
    int id, p, r = 1000, fin = 2500;
    MPI_Status status;
    MPI_Init(&argc, &argv); // Initialize MPI.
    MPI_Comm_size(MPI_COMM_WORLD, &p); // Get the number of processes.
    MPI_Comm_rank(MPI_COMM_WORLD, &id); // Get the individual process ID.
    // Print off a hello world message
    if(id==0 && fin>r){
        MPI_Send(&r,1,MPI_INT,id+1,0,MPI_COMM_WORLD);
    }
    while(fin-r-p+1 > 0){
            MPI_Recv(&r,1,MPI_INT,(id-1)%p,0,MPI_COMM_WORLD,&status);
            std::cout << " ID = " << id << " " << r << std::endl;
            r++;
            if(r == fin+1){
                break;
            }
            MPI_Send(&r,1,MPI_INT,(id+1)%p,0,MPI_COMM_WORLD);
    }
    MPI_Finalize(); // Terminate MPI.
    return 0;
}