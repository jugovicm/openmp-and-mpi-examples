#include <stdio.h>
#include <string.h>
#include <mpi.h>
#include <stdlib.h>
#include <time.h>
const int MAX_STRING = 100;

int main (void) {
	char gret[MAX_STRING];
	char out[MAX_STRING];
	
	int csize;
	int prank;
	int num_rand;
	
	MPI_Init(NULL, NULL);
	
	MPI_Comm_size(MPI_COMM_WORLD, &csize);

	MPI_Comm_rank(MPI_COMM_WORLD, &prank);
	
	srand(prank);
	srand(time(0)); // da ne dobijemo uvek iste borjeve
	
	for (int i = 0; i < csize; i++){
		if (i != prank) {
			num_rand = prank*10+rand() % 10;
			sprintf(gret, "%d ", num_rand);
			MPI_Send(gret, strlen(gret)+1, MPI_CHAR, i, 0, MPI_COMM_WORLD);
		}
	}
	
	for(int i = 0; i < csize; i++){
		if (i != prank) {
			MPI_Recv(gret, MAX_STRING, MPI_CHAR, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			strcat(out, gret);			
		}				
	}
	
	printf("Process %d received %s\n", prank, out);

	MPI_Finalize();
	
	return 0;
}

