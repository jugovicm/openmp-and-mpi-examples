all:
	make main run clean
main:
	mpic++ -o z3 z3.c
run:
	mpiexec --oversubscribe -np 6 ./z3 vec.txt mat.txt
.PHONY: clean
clean:
	rm -rf z3 trs.txt
