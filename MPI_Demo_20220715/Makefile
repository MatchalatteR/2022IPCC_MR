all: MPI_Version No_MPI_Version CaculatePI_Complete_Version
.PHONY: all

MPI_Version:MPI_Computing_PI.o
	mpic++ -o MPI_Version MPI_Computing_PI.o
 
No_MPI_Version:Computing_PI.o
	g++ -o No_MPI_Version Computing_PI.o

CaculatePI_Complete_Version:CaculatePI.o
	mpicxx -o CaculatePI_Complete_Version CaculatePI.o

CaculatePI.o:CaculatePI.c
	mpic++ -c CaculatePI.c

MPI_Computing_PI.o:MPI_Computing_PI.c
	mpic++ -c MPI_Computing_PI.c

Computing_PI.o:Computing_PI.c
	g++ -c Computing_PI.c

clean:
	rm -f MPI_Version No_MPI_Version Computing_PI.o MPI_Computing_PI.o CaculatePI_Complete_Version CaculatePI.0
