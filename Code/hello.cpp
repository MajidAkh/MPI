#include <iostream>
#include <mpi.h>

int main (int argc, char *argv[]) {
    int id, p, name_len;
    char name[MPI_MAX_PROCESSOR_NAME];
    //char processor_name[MPI_MAX_PROCESSOR_NAME];
    MPI_Init(&argc, &argv); // Initialize MPI.
    MPI_Comm_size(MPI_COMM_WORLD, &p); // Get the number of processes.
    MPI_Comm_rank(MPI_COMM_WORLD, &id); // Get the individual process ID.
    MPI_Get_processor_name(name, &name_len);
    // Print off a hello world message
    std::cout << "Machine = " << name << " ID = " << id << " Hello World !" << std::endl;
    MPI_Finalize(); // Terminate MPI.
    return 0;
}