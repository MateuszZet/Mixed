#include<mpi.h>
#include <time.h>
#include <stdlib.h>
#include <mpi.h>
#include <unistd.h>

void oneToAllPersRing(int sendMsg, int sendSize, int recvMsg);

int main (int argc, char **argv){
//wlaczenie MPI
MPI_Init(&argc, &argv);
//kod
//jest 6 procesow od 0 do 5 poczatkowy musi byc 0 koncowy mozna ustalic na mniejszy niz 5
oneToAllPersRing(0,1,5);
//odlaczenie
MPI_Finalize();
return 0;}




void oneToAllPersRing(int sendMsg, int sendSize, int recvMsg){
  int messages[6] = {0,1,2,3,4,5};
  int rank, size;
  int next, prev, sendval;
  int x;
  double s0, s, r, r0;

MPI_Comm_rank(MPI_COMM_WORLD, &rank);
MPI_Comm_size(MPI_COMM_WORLD, &size);

if (size > 1)
    {
        for(x=recvMsg;x>0;x--)
        {
        sendval = messages[x];
         if(rank == sendMsg){
            s0 = MPI_Wtime();
            MPI_Send(&sendval, 1, MPI_INT, rank+1, 1, MPI_COMM_WORLD);
			  s = MPI_Wtime();
            printf("[Process %d]: Sended %d to process %d               (MPI_Send Time: %f)\n", rank,  sendval, rank+1, s-s0);
        }else if(rank < x){
            s0 = MPI_Wtime();
            MPI_Send(&sendval, 1, MPI_INT, rank+1, 1, MPI_COMM_WORLD);
            s = MPI_Wtime();
            printf("[Process %d]: Sended %d to process %d               (MPI_Send Time: %f)\n", rank,  sendval, rank+1, s-s0);

            r0 = MPI_Wtime();
            MPI_Recv(&sendval, 1, MPI_INT, rank-1, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            r = MPI_Wtime();
            printf("[Process %d]: Received %d from process %d           (MPI_Recv Time: %f)\n", rank, sendval, rank-1, r-r0);
        }
        if(x == rank){
        printf("Process %d received %d END\n", rank, sendval);
        }
        }

    }
}