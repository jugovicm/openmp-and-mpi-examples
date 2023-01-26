all: 
	make main run clean
main:
	mpicc z1.c -o z1o
run:
	mpiexec --oversubscribe -np 6 ./z1o
.PHONY: clean
clean:
	-rm -rf z1o
