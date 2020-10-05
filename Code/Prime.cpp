#include <mpi.h>
#include <cmath>
#include <iostream>
#include <limits>
#include <algorithm>

using namespace std;

bool isPrimeQ1Seq(unsigned long long n){
    if(n=2){
        return true;
    }
    if(n%2==0){
        return false;
    }
    unsigned long sr = sqrt(n);
    for(unsigned long i=3; i<sr; i+= i+2){
        if(n%i == 0){
            return false;
        }
    }
    return true;
}


bool isPrimeQ1Omp(unsigned long long n){
    int result,sol = true;
    int id,p;
     MPI_Status status;
    MPI_Comm_size(MPI_COMM_WORLD, &p); // Get the number of processes.
    MPI_Comm_rank(MPI_COMM_WORLD, &id); // Get the individual process ID.
    if(n==1 || n==2 || n==3|| n==5 || n==7){
        result = true;
    }else if(n%2==0 || n%5==0){
        result = false;
    }else{
    unsigned long sr = floor(sqrt(n));
    
    unsigned long j = floor(p/4);
    if(id%4 == 0){
        for(unsigned long i=1+10*floor(id/4)+1; i<sr; i+= i+j){
            if(n%i == 0){
                sol = false;
                cout<< i <<endl;
            }
        }
    }
    if(id%4 == 1){
        for(unsigned long i=3+10*floor(id/4); i<sr; i+= i+j){
            if(n%i == 0){
                sol = false;
                 cout<< i <<endl;
            }
        }
    }
    if(id%4 == 2){
        for(unsigned long i=7+10*floor(id/4); i<sr; i+= i+j){
            if(n%i == 0){
                sol = false;
                cout<< i <<endl;
            }
        }
    }
    if(id%4 == 3){
        for(unsigned long i=9+10*floor(id/4); i<sr; i+= i+j){
            if(n%i == 0){
                sol = false;
                cout<< i <<endl;
            }
        }
    }
    MPI_Reduce(&sol, &result, 1, MPI_INT, MPI_PROD, 0, MPI_COMM_WORLD);
    }
    if(id == 0){
        cout << result <<endl;
    }
}

bool isPrimeQ4(unsigned long long n){
    int id,p, flag;
    MPI_Comm_size(MPI_COMM_WORLD, &p); // Get the number of processes.
    MPI_Comm_rank(MPI_COMM_WORLD, &id); // Get the individual process ID.
    MPI_Status stats[2];
    if(n==1 || n==2 || n==3|| n==5 || n==7){
        if(id == 0){
          cout << true <<endl;
        }
    }else if(n%2==0 || n%5==0){
        if(id == 0){
          cout << false <<endl;
        }
    }else if(id == 0){
        int cpp;
        int* sol = new int[p-1];
        MPI_Request reqs[p-1];
        for(int i = 1; i<p;i++){
            MPI_Irecv (&sol[i], 1, MPI_INT, i, 0, MPI_COMM_WORLD, &reqs[i]);
        }
        while(cpp < p-1){
            cpp = 0;
            for(int i = 1; i<p;i++){
                MPI_Request_get_status(reqs[i],&flag,&stats[0]);
                if(flag && !sol[i]){
                    for(int i = 1; i<p;i++){
                        MPI_Isend(&sol[i], 1, MPI_INT, i, 0, MPI_COMM_WORLD, &reqs[0]);
                        cpp = p;
                    }
                }else if(flag){
                    cpp++;
                }
            }
        }
        if(cpp == p-1){
            cout << true <<endl;
        }else{
            cout << false <<endl;
        }
    }else{
        int sol = true;
        MPI_Request reqs[2];
        MPI_Irecv(&sol, 1, MPI_INT, 0, 1, MPI_COMM_WORLD, &reqs[0]);
        unsigned long sr = floor(sqrt(n));
        unsigned long j = floor(p/4);
        if(id%4 == 0 && id!=0){
            for(unsigned long i=1+10*floor(id/4)+1; i<sr; i+= i+j){
                MPI_Request_get_status(reqs[0],&flag,&stats[0]);
                if(flag){
                    break;
                }
                if(n%i == 0){
                    sol = false;
                    MPI_Isend(&sol, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &reqs[1]);
                }
            }
        }
        if(id%4 == 1){
            for(unsigned long i=3+10*floor(id/4); i<sr; i+= i+j){
                MPI_Request_get_status(reqs[0],&flag,&stats[0]);
                if(flag){
                    break;
                }
                if(n%i == 0){
                    sol = false;
                    MPI_Isend(&sol, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &reqs[1]);
                }
            }
        }
        if(id%4 == 2){
            for(unsigned long i=7+10*floor(id/4); i<sr; i+= i+j){
                MPI_Request_get_status(reqs[0],&flag,&stats[0]);
                if(flag){
                    break;
                }
                if(n%i == 0){
                    sol = false;
                    MPI_Isend(&sol, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &reqs[1]);
                }
            }
        }
        if(id%4 == 3){
            for(unsigned long i=9+10*floor(id/4); i<sr; i+= i+j){
                MPI_Request_get_status(reqs[0],&flag,&stats[0]);
                if(flag){
                    break;
                }
                if(n%i == 0){
                    sol = false;
                    MPI_Isend(&sol, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &reqs[1]);
                }
            }
        }
        if(sol){
            MPI_Isend(&sol, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &reqs[1]);
        }
    }
}



int main(int argc, char *argv[]) {

    int id;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &id);
    isPrimeQ4(stoull(argv[1]));
    MPI_Finalize();
    cout << isPrimeQ1Seq(stoull(argv[1]));
    return 0;
    
   
}