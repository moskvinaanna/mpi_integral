// mpi_integral.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <math.h>
#include "mpi.h"

using namespace std;

double integral(double a, double b, double n) {
	double h = (b - a) / n;
	double res = 0;

	for (int i = 0; i < n; i++) {
		res += sin(a + i * h + h/2) * h;
	}
	return res;
}

int main(int argc, char *argv[])
{
	MPI_Init(&argc, &argv);
	int rank;
	double buf[2];
	MPI_Request request;
	MPI_Status status;

	MPI_Comm_rank(MPI_COMM_WORLD, &rank);


	if (rank == 0 || rank == 1) {
		double integ = integral(rank*10, (rank+1)*10, 1000);
		MPI_Isend(&integ, 1, MPI_DOUBLE, 2, 0, MPI_COMM_WORLD, &request);
	}

	if (rank == 2) {
		MPI_Recv(&buf[0], 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD, &status);
		MPI_Recv(&buf[1], 1, MPI_DOUBLE, 1, 0, MPI_COMM_WORLD, &status);
		double integ = integral(20, 30, 1000) + buf[0] + buf[1];
		cout << "Result " << integ << endl;
	}

	MPI_Finalize();
	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
