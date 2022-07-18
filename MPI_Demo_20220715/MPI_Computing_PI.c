#include<mpi.h>
#include<iostream>
#include<math.h>
#include<time.h>
#include<iomanip>
//#include<unistd.h>

#define N1 10000000
#define N2 100000000
#define N3 1000000000
#define pi_tag 100
#define coststime_tag 200

using namespace std;

int main(int argc, char* argv[]) {
	MPI_Init(&argc, &argv);
	double recv_pi;
	
	clock_t start, end;
	double final_costs, recv_costs, coststime;

	int Comm_rank, Comm_size;
	MPI_Comm_size(MPI_COMM_WORLD, &Comm_size);
	MPI_Comm_rank(MPI_COMM_WORLD, &Comm_rank);
	int group = N3/(Comm_size-1);
	
	if (Comm_rank != 0) {//other process
		double pi = 0.0;
		clock_t start, end;
		double coststime;
		start = MPI_Wtime();
		for (int i = (Comm_rank-1)*group+1; i <= Comm_rank * group; i++) {
			double x = (i * 1.0) / N3;
			pi += sqrt(1 - x * x);
		}
		end = MPI_Wtime();
		coststime = (double)(end - start) / CLOCKS_PER_SEC;
		MPI_Send(&pi, 1, MPI_DOUBLE, 0, pi_tag, MPI_COMM_WORLD);
		MPI_Send(&coststime,1,MPI_LONG,0,coststime_tag,MPI_COMM_WORLD);
	}
	else {//main process
		double final_pi = 0.0;
		for (int i = 1; i < Comm_size; i++) {
			MPI_Recv(&recv_pi, 1, MPI_DOUBLE, i, pi_tag, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			MPI_Recv(&recv_costs,1,MPI_LONG,i,coststime_tag,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
			final_pi += recv_pi;
			final_costs+=recv_costs;
		}
		final_pi = (final_pi * 4) / N3;
		final_costs/=(Comm_size-1);
		cout << "func1(N3) costs " << setprecision(10)<< final_costs << "s" << endl;
		cout << setprecision(100) << "Pi = " << final_pi << endl;
	}
	
	MPI_Finalize();
	
	return 0;
}

/*
#define DATATAG 100
int main(int argc, char* argv[]) {
	MPI_Init(&argc, &argv);
	int Comm_size,Comm_rank;
	double Recvdata;
	MPI_Comm_rank(MPI_COMM_WORLD, &Comm_rank);
	MPI_Comm_size(MPI_COMM_WORLD, &Comm_size);
	if(Comm_rank!=0){
		double data = 1.0;
		for (int i = Comm_rank; i < Comm_size; i++) {
			data++;
		}
		printf("My data is %f\n",data);
		MPI_Send(&data, 1, MPI_DOUBLE, 0, DATATAG, MPI_COMM_WORLD);
	}
	else {
		double Finaldata=0.0;
		for (int i = 1; i < Comm_size; i++) {
			MPI_Recv(&Recvdata, 1, MPI_DOUBLE, i, DATATAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			Finaldata += Recvdata;
		}
		cout << "Finaldata is " << Finaldata << endl;
	}

	MPI_Finalize();
	return 0;
}
*/

/*const int MAX_STRING = 100;

int main(int argc,char* argv[]) {
	char greeting[MAX_STRING];
	int comm_sz;
	int my_rank;
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

	if (my_rank != 0) {
		sprintf(greeting, "Greeting from process %d of %d!", my_rank, comm_sz);
		MPI_Send(greeting, strlen(greeting) + 1, MPI_CHAR, 0, 0, MPI_COMM_WORLD);
	}
	else {
		printf("Greeting from process %d of %d!\n", my_rank, comm_sz);
		for (int q = 1; q < comm_sz; q++) {
			MPI_Recv(greeting, MAX_STRING, MPI_CHAR, q, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			printf("%s\n", greeting);
		}
	}
	MPI_Finalize();
	return 0;
}*/


