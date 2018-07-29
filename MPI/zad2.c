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
int number = 210040;
int a;
while(a<1){
//printf("myrank = %d\n", myrank);
if(myrank == 0){
MPI_Send(&number,1,MPI_INT, 1,0,MPI_COMM_WORLD);
printf("Proces %d wyslal %d\n",myrank, number);
MPI_Recv(&number, 1,MPI_INT, 1,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
printf("Proces %d otrzymal %d\n",myrank, number);}

if(myrank == 1){
MPI_Recv(&number,1,MPI_INT,0,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
printf("Proces %d otrzymał %d\n",myrank, number);
printf("Inkrementacja %d +1111\n", number);
number = number + 1111;
MPI_Send(&number,1,MPI_INT,0,0,MPI_COMM_WORLD);
printf("Proces %d wyslal %d\n",myrank, number);}
a++;
}
//odlaczenie
MPI_Finalize();
return 0;}
