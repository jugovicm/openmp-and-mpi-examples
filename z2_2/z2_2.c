#include <stdio.h>
#include <mpi.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

#define MAX_ELEMENT 10

int main(int argc, char* argv[]){

	double sum = 0;
	double tsum = 0;
	double first[MAX_ELEMENT], second[MAX_ELEMENT];
	int csize, prank;

	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &csize);
	MPI_Comm_rank(MPI_COMM_WORLD, &prank);
	
	srand(time(0));
	
	if (prank == 0){		
		for(int i = 0; i < MAX_ELEMENT; i++){
			first[i] = rand()%10;
			second[i] = rand()%10;
		}
		
		for(int i = 0; i < MAX_ELEMENT; i++)
			printf("first[%d] = %f\tsecond[%d] = %f\n", i, first[i], i, second[i]);
	}
		
	MPI_Bcast(&first, MAX_ELEMENT, MPI_DOUBLE, 0, MPI_COMM_WORLD);
	MPI_Bcast(&second, MAX_ELEMENT, MPI_DOUBLE, 0, MPI_COMM_WORLD);
		
	int i=prank;	
	
	while(i<=MAX_ELEMENT){
		sum += second[i]*first[i];
		i += csize;
	}
	
	MPI_Reduce(&sum, &tsum, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
	
	if (prank == 0) {
		printf("Sum = %lf\n", tsum);
	}
	
	MPI_Finalize();
	
	return 0;
}
