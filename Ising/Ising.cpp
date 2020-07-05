#include <iostream>
#include<cmath>
#include <iomanip>
#include<fstream>
#include"Ising mode of function.h"
//#include"prngcl_ranecu.cl.h"
#include <random>
#include<stdlib.h>
#include<time.h>
//#include<thread>


using namespace std;


double randomofjm()
{
	double r;
	static default_random_engine e;
	static uniform_real_distribution<double> u(0, 1);
	r = u(e);
	return  r;
	/*static double a;
	static double b;
	static double r;
	static random_device rd;
	a = rd();
	b = rd.max();
	r = (a / b);
	return r;*/


}


int main(void)
{
	//double T;
	double sum = 0;
	double sum_m = 0;
	double sum_m2 = 0;
	double sum_m4 = 0;
	double sum_e = 0;
	double sum_e2 = 0;
	double point_magnetization = 0;
	double Binder;
	double magnet4, magnet4_perSpin;
	double magnet2, magnet2_perSpin;
	double energy2, energy2_perSpin;
	double Energy, Energy_perSpin;
	double Magnetization, Magnetization_perSpin;
	int Spins[L][L];
	int InitialSpin = 1;
	ofstream file0;
	double s = 0;

	Magnetization = Magnetization_total(Spins);
	file0.open("new2DIsingMode7.2L_32T0-0.3.txt");
	file0 << "temperature \t <E> \t <E^2> \t <m> \t <m^2>" << endl;
	file0 << "## Monte Carlo Simulation for 2D Ising Model with Periodic Boundary conditions" << endl;
	file0 << "## Algorithm : Metropolis Algorithm" << endl;
	file0 << "## Random Number type: 	uniform_real_distribution<double> u(0, 1);" << endl;
	file0 << "## L = " << L << endl;
	file0 << "## Strength of the Magnetic Field: H = " << H << endl;
	file0 << "## Total Monte Carlo Time =  " << TotalTime << endl;
	file0 << "## Relaxation Time =  " << RelaxationTime << endl;
	file0 << "temperature" << "\t" << setw(15) << " <E>" << "\t" << setw(13) << "<E^2>" << "\t" << setw(28) << " <m>" << "\t" << setw(30) << " <m^2> " << endl;
	Initialization(InitialSpin, Spins);
	Energy = Energy_total(Spins);
	Magnetization = Magnetization_total(Spins);
	for (double j = 0.0; j < 0.3; j = j + 0.01)
	{

		sum = 0.0;
		int  Number = 0;
		sum_m = 0.0;
		sum_m2 = 0.0;
		sum_m4 = 0.0;
		sum_e = 0.0;
		sum_e2 = 0.0;
		point_magnetization = 0.0;
		T = j;
		cout << j << endl;
		//		double total_m2 = 0, total_m4 = 0, total_e2 = 0;

		for (int k = 0; k < TotalTime; k++)
		{
			MonteCarloSweep(Spins, Energy, Magnetization, magnet2, energy2, T);
			if (k >= RelaxationTime)
			{
				if ((k % 10) == 0)
				{
					Magnetization_perSpin = Magnetization / (double(L) * L);
					//Magnetization_perSpin = fabs(Magnetization_perSpin);//no need to have a absolute value.
					sum_m = sum_m + Magnetization_perSpin;
					Energy_perSpin = Energy / (double(L) * L);
					sum_e = sum_e + Energy_perSpin;
					magnet2_perSpin = magnet2 / (double(L) * L * L * L);
					sum_m2 = sum_m2 + magnet2_perSpin;
					energy2_perSpin = energy2 / (double(L) * L * L * L);
					sum_e2 = sum_e2 + energy2_perSpin;





				}
			}
		}
		file0 << T << "\t" << setw(30) << (sum_e / 10000.0) << "\t" << setw(30) << (sum_e2 / 10000.0) << "\t" << setw(30) << (sum_m / 10000.0) << "\t " << setw(30) << (sum_m2 / 10000.0) << "\t ";

		//		file0 << T << "\t" << setw(30) <<  Binder*3/2.0 << "\t" << setw(30) << (sum_m / 10000.0) << "\t"<< setw(30) << (sum_m2 / 10000.0) << "\t "<< setw(30) << (sum_m4 / 10000.0) << "\t ";
		file0 << endl;

	}

	file0.close();
	return 0;
}

