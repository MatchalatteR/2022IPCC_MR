
#include<iostream>
#include<math.h>
#include<time.h>
#include<iomanip>
#include<unistd.h>

#define N1 10000000
#define N2 100000000
#define N3 1000000000

using namespace std;

void func1_N1(){
	double pi = 0.0;
	clock_t start,end;
	double coststime;	
	start = clock();
	for(int i=1;i<=N1;i++){
		double x = (i*1.0)/N1;
		pi+=sqrt(1-x*x);
	}
	pi = (pi*4)/N1;
	end = clock();
	coststime = (double)(end-start)/CLOCKS_PER_SEC;
	cout << "func1(N1) costs " << coststime << "s" << endl;
	cout << setprecision(100) << "Pi = " << pi << endl;
}

void func1_N2(){
	double pi = 0.0;
	clock_t start,end;
	double coststime;	
	start = clock();
	for(int i=1;i<=N2;i++){
		double x = (i*1.0)/N2;
		pi+=sqrt(1-x*x);
	}
	pi = (pi*4)/N2;
	end = clock();
	coststime = (double)(end-start)/CLOCKS_PER_SEC;
	cout << "func1(N2) costs " << setprecision(6)<< coststime << "s" << endl;
	cout << setprecision(100) <<"Pi = " << pi << endl;
}

void func1_N3(){
	double pi = 0.0;
	clock_t start,end;
	double coststime;	
	start = clock();
	for(int i=1;i<=N3;i++){
		double x = (i*1.0)/N3;
		pi+=sqrt(1-x*x);
	}
	pi = (pi*4)/N3;
	end = clock();
	coststime = (double)(end-start)/CLOCKS_PER_SEC;
	cout << "func1(N3) costs " << setprecision(6)<< coststime << "s" << endl;
	cout << setprecision(100) <<"Pi = " << pi << endl;
}

void Simple_func(){
	cout<< "Program start" << endl;
	cout<< "********************" << endl;
	sleep(2);
	func1_N1();
	cout<< "********************" << endl;
	sleep(2);
	func1_N2();
	cout<< "********************" << endl;
	func1_N3();
	sleep(2);
}

int main(int argc, char* argv[]){
	Simple_func();
	cout<<"Next, using mpi parallel pograming"<< endl;
	return 0;
}
