all: 
	make main run clean
main:
	mpicc z2_1.c -o z2
run:
	mpiexec --oversubscribe -np 6 ./z2
.PHONY: clean
clean:
	-rm -rf z2
