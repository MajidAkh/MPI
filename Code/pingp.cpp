#include <iostream>
#include <mpi.h>

int main (int argc, char *argv[]) {
    int id, p, r;
    int fin = 100;
    MPI_Status status;
    MPI_Init(&argc, &argv); // Initialize MPI.
    MPI_Comm_size(MPI_COMM_WORLD, &p); // Get the number of processes.
    MPI_Comm_rank(MPI_COMM_WORLD, &id); // Get the individual process ID.
    // Print off a hello world message
    if(id%2 == 0){
        MPI_Send(&id,1,MPI_INT,id+1,0,MPI_COMM_WORLD);
        r = id;
        while(r < fin - 10){
            MPI_Recv(&r,1,MPI_INT,id+1,0,MPI_COMM_WORLD,&status);
            r = r + 1;
            std::cout << " ID = " << id << " " << r << std::endl;
            if(r < fin){
                MPI_Send(&r,1,MPI_INT,id+1,0,MPI_COMM_WORLD);
            }
        }

    }else{
        do{
            MPI_Recv(&r,1,MPI_INT,id-1,0,MPI_COMM_WORLD,&status);
            r = r + 10;
            std::cout << " ID = " << id << " " << r << std::endl;
            if(r < fin){
                MPI_Send(&r,1,MPI_INT,id-1,0,MPI_COMM_WORLD);
            }
        }while(r < fin-1);
    }

    MPI_Finalize(); // Terminate MPI.
    return 0;
}