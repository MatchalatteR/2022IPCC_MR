#include"mpi.h"
#include<iostream>
#include<math.h>
#include<time.h>
#include<iomanip>

#define N 1000000000
#define pi_tag 100
#define coststime_tag 200

using namespace std;

void Simple_Caculate(){
	double pi = 0.0;
	clock_t start,end;
	start = clock();
	for(int i=1;i<=N;i++){
		double x = (i * 1.0) / N;
		pi += sqrt(1 - x * x);
	}
	end = clock();
	pi = (pi*4)/N;
	double coststime = (double)(end - start) / CLOCKS_PER_SEC;
	cout << "Simple_Caculate costs " << setprecision(10)<< coststime << "s" << endl;
	cout << setprecision(100) << "Pi = " << pi << endl;
}

void MPI_Caculate(int comm_sz){
	double final_pi = 0.0;
	double final_costs = 0.0;
	double recv_pi,recv_costs;
	
	for(int i=1;i<comm_sz;i++){
		MPI_Recv(&recv_pi, 1, MPI_DOUBLE, i, pi_tag, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		MPI_Recv(&recv_costs,1,MPI_DOUBLE,i,coststime_tag,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
		final_pi += recv_pi;
		final_costs+=recv_costs;
	}
	final_pi = (final_pi * 4)/N;
	final_costs/=(comm_sz-1);
	cout << "MPI Function costs " << setprecision(10)<< final_costs << "s" << endl;
	cout << setprecision(100) << "Pi = " << final_pi << endl;
}

int main(int argc, char** argv){
	MPI_Init(&argc,&argv);
	int comm_rk,comm_sz;
	MPI_Comm_rank(MPI_COMM_WORLD,&comm_rk);
	MPI_Comm_size(MPI_COMM_WORLD,&comm_sz);	
	int group = N/(comm_sz-1);
	if(comm_rk==0){//main process
		cout<<"***********Program start*************"<<endl;
		Simple_Caculate();
		cout<<"***********MPI Function start*************"<<endl;
		MPI_Caculate(comm_sz);
		cout<<"***********Program end*************"<<endl;		
	}else{
		double x;
		double pi = 0.0;
		clock_t start,end;
		start = clock();
		for(int i = (comm_rk-1)*group+1; i <= comm_rk * group; i++){
			x = (i * 1.0) / N;
			pi += sqrt(1 - x * x);
		}
		end = clock();
		double coststime = (double)(end - start) / CLOCKS_PER_SEC;
		MPI_Send(&pi, 1, MPI_DOUBLE, 0, pi_tag, MPI_COMM_WORLD);
		MPI_Send(&coststime,1,MPI_DOUBLE,0,coststime_tag,MPI_COMM_WORLD);
	}
	MPI_Finalize();
	return 0;
}
