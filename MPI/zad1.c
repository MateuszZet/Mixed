#include<mpi.h>

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
printf("myrank = %d\n", myrank);
int number = 210040;
if(myrank == 0){
MPI_Send(&number,1,MPI_INT, 1,0,MPI_COMM_WORLD);
printf("Proces 0 wyslal %d do procesu 1\n", number);
}
else if (myrank == 1){
MPI_Recv(&number,1,MPI_INT,0,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
printf("Proces 1 otrzymał %d od procesu 0\n", number);
}
//odlaczenie
MPI_Finalize();
return 0;}
