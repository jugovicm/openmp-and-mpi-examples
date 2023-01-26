#include <stdio.h>
#include <mpi.h>
#include <math.h>

int getInput() {
	int res;
	
	printf("Number: ");
	fflush(stdout);
	scanf("%d", &res);
	
	return res;
}

int main(int argc, char* argv[]){
	int n;
	int zbir = 0;
	int total_zbir;
	int csize, prank;
	//int i;
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &csize);
	MPI_Comm_rank(MPI_COMM_WORLD, &prank);
	
	if (prank == 0)
		n = getInput();
		
	MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);
	
	double s = MPI_Wtime();
	int velicina, prvi, poslednji;

	velicina = n/(csize);
	prvi = prank*velicina + prank;
	
	if(velicina + prvi < n){
		poslednji = prvi + velicina; //zbog poslednjeg clana 
	}
	else{
		poslednji = n;
	}
	
	for (int i = prvi; i<= poslednji; i++){
		zbir += i;
	}

	MPI_Reduce(&zbir, &total_zbir, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
	
	if (prank == 0) {
		printf("Zbir %d prirodnih brojeva je = %d\n", n, total_zbir);
	}

	MPI_Finalize();
	
	return 0;
}

