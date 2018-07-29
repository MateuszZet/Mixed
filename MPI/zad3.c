#include<mpi.h>
#include <time.h>
#include <stdlib.h>

int main (int argc, char **argv){

int myrank;
int comm_size;

//wlaczenie MPI
MPI_Init(&argc, &argv);

//pobranie numeru procesu
MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
//pobranie liczby procesow
MPI_Comm_size(MPI_COMM_WORLD, &comm_size);

//kod
int number;
if (myrank != 0) {
  MPI_Recv(&number, 1, MPI_INT, myrank - 1, 0,
             MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    printf("Proces %d otrzymal %d od %d\n",
           myrank, number, myrank - 1);
} else {
    number = 210040;
}

srand(time(NULL));
number =number + rand() % 10000;
MPI_Send(&number, 1, MPI_INT, (myrank + 1) % comm_size,
         0, MPI_COMM_WORLD);

if (myrank == 0) {
    MPI_Recv(&number, 1, MPI_INT, comm_size - 1, 0,
             MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    printf("Proces %d otrzymal %d od %d\n",
           myrank, number, comm_size - 1);
}
//odlaczenie
MPI_Finalize();
return 0;}
