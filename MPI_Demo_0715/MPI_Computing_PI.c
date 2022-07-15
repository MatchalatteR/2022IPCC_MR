#include<mpi.h>
#include<iostream>
#include<math.h>
#include<time.h>
#include<iomanip>
#include<unistd.h>

#define N1 10000000
#define N2 100000000
#define N3 1000000000
#define pi_tag 100
#define coststime_tag 200

using namespace std;

int main(int argc, char* argv[]){
	MPI_Init(&argc,&argv);
	double recv_pi;
	double final_pi = 0.0;
	clock_t start,end;
	double final_costs,recv_costs,coststime;

	int Comm_rank,Comm_size;
	MPI_Comm_size(MPI_COMM_WORLD,&Comm_size);
	MPI_Comm_rank(MPI_COMM_WORLD,&Comm_rank);
	/*using N3 as para*/	
	int group = N3/Comm_size;
	if(Comm_rank!=0){//other process
		double pi = 0.0;
		clock_t start,end;
		double coststime;	
		start = clock();
		for(int i = (Comm_rank-1)*group;i<Comm_rank*group;i++){
			double x = (i*1.0)/N3;
			pi += sqrt(1-x*x);
		}
		end = clock();
		coststime = (double)(end-start)/CLOCKS_PER_SEC;
		MPI_Send(&pi,1,MPI_DOUBLE,0,pi_tag,MPI_COMM_WORLD);
		//MPI_Send(&coststime,1,MPI_LONG,0,coststime_tag,MPI_COMM_WORLD);
	}else{//main process
		for(int i=1;i<=Comm_size;i++){
			MPI_Recv(&recv_pi,1,MPI_DOUBLE,i,pi_tag,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
			//MPI_Recv(&recv_costs,1,MPI_LONG,i,coststime_tag,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
			final_pi+=recv_pi;
			//final_costs+=recv_costs;		
		}
		final_pi = (final_pi*4)/N3;
		//cout << "func1(N3) costs " << setprecision(6)<< final_costs << "s" << endl;
		cout << setprecision(100) <<"Pi = " << final_pi << endl;
	}	
	MPI_Finalize();
	return 0;
}
