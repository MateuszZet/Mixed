#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX 10000
#include <unistd.h> // sleep

struct elem { 
        float val; 
        int   rank; 
    } gmin,lmin;

// wypelnienie tablicy
void FilltheArray(struct elem *tab, int N){  
	int i;

	for(i=0;i<N;i++){
		tab[i].val=(float)rand()/(float)MAX;
		tab[i].rank = 0;
		}
}

struct elem Min(struct elem *tab, int N, int myid){
	float minimum;
	int i,j, pmin;
	for(i=0; i<N; i++){
	tab[0].rank = myid;
	pmin = i;
		for(j=i+1;j<N;j++){
			if(tab[j].val<tab[pmin].val){
				pmin = j;
		}
		
	}
		minimum = tab[i].val;
		tab[i].val = tab[pmin].val;
		tab[pmin].val = minimum;
			
	}
	return tab[0];
}


// wypisanie zawartosci tablicy
void Myprint(struct elem *tab, int N){
	int i;
	for(i=0;i<N;i++)
		printf("Id: %d  Value: %f\n",i,tab[i].val);	
}

/***************** MAIN **********************/
int main(int argc,char *argv[]){
	int myid, numprocs;
	srand(time(NULL));
	//inicjalizacja MPI
	MPI_Init(&argc,&argv);
	MPI_Comm_size(MPI_COMM_WORLD,&numprocs);
	MPI_Comm_rank(MPI_COMM_WORLD,&myid);

	//int i,j;  
	float temp; // zmienna tymczasowa
    int N, done, part; // N: wielkosc tablicy | part: czesc tablicy
	struct elem *tab, *tab_part, *tab2; 
	//int gmin;
	double t0,t1, s0, s1, r0, r1; //czas przed i po
	r0 = MPI_Wtime();
	N = atoi(argv[1]);
	
	if(myid == 0){
		printf("MPI SELECTION SORT\n");
		tab = (struct elem*)malloc(N*sizeof(struct elem));
		tab2 = (struct elem*)malloc(N*sizeof(struct elem));
		FilltheArray(tab,N); //utworzenie tablicy
		
		if(N%numprocs!=0){
			printf("\nWielkosc tablicy nie jest podzielna przez liczbe procesow (N\numprocs)! \n");
			exit(1);
		}
		
		part = (N/numprocs);  // obliczenie wielkosci czesci
		
		
		
		printf("Liczba procesow(numprocs): %d Wielkosc tablicy (N): %d Wielkosc czesci (part): %d\n",numprocs,N,part);		

		Myprint(tab,N);  //wypisanie tablicy
		}
		
	MPI_Bcast(&part,1,MPI_INT,0,MPI_COMM_WORLD);
	tab_part=(struct elem*)malloc(part*sizeof(struct elem));
	MPI_Scatter(tab,part,MPI_FLOAT_INT,tab_part,part,MPI_FLOAT_INT,0,MPI_COMM_WORLD); 
	
	//zakomentowac - tylko do wizualizacji
	sleep(myid*1);
	printf("Czesc %d\n", myid);
	Myprint(tab_part,part);
	sleep(numprocs-myid);
	printf("\n");	
	
	
	int pos=0,proc=0,counter=0;
	t0 = MPI_Wtime();
	
	if(numprocs !=1){
	//FILE *f = fopen("times.csv", "w");
	while(proc < numprocs){
	
	
		
	struct elem *p = &tab_part[pos];
	
	if (myid == proc){
	lmin=Min(p, part-pos, myid);}
	
	if (myid > proc){
		lmin=Min(tab_part, part, myid);
	}
	
	//printf("numprocs: %d , min: %f\n", lmin.rank, lmin.val);
	MPI_Allreduce(&lmin, &gmin, 1, MPI_FLOAT_INT, MPI_MINLOC, MPI_COMM_WORLD);
	//printf("Global min: %f, numproc: %d\n",gmin.val, gmin.rank);
	
	if(proc != gmin.rank){
	if(myid == proc){
		MPI_Send(&tab_part[pos].val,1,MPI_FLOAT,gmin.rank,0,MPI_COMM_WORLD);
		MPI_Recv(&tab_part[pos].val,1,MPI_FLOAT,gmin.rank,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
	}
	
	if(myid==gmin.rank){
		
		MPI_Send(&tab_part[0].val,1,MPI_FLOAT,proc,0,MPI_COMM_WORLD);
		MPI_Recv(&tab_part[0].val,1,MPI_FLOAT,proc,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
	}
	
	
	
	}
	
	pos++;
	counter++;
	
	if(pos==part){
		proc++;
		pos=0;
	} 
	
	}
	}
	//fclose(f);
	
	/*
	sleep(myid*1);
	printf("Czesc %d\n", myid);
	Myprint(tab_part,part);
	sleep(numprocs-myid);
	printf("\n");
	*/
	

	MPI_Gather(&tab_part[0], part,  MPI_FLOAT_INT, &tab2[0], part,MPI_FLOAT_INT,0,MPI_COMM_WORLD);
	t1 = MPI_Wtime();
	r1 = MPI_Wtime();
	if (myid==0){
		Min(tab2,N,0);
		Myprint(tab2,N);
		printf("Czas wykonania calego programu: %.16f\n",r1-r0);
		printf("Czas sortowania (algorytmu): %.16f\n",t1-t0);
	}
		
	
	MPI_Finalize();
	return 0;
}
