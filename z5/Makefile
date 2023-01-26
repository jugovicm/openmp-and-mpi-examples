all:
	make main run clean
main: 
	g++ -fopenmp -Wall -o z5 z5.c
run:
	./z5
.PHONY: clean
clean:
	rm -rf z5 res.txt
