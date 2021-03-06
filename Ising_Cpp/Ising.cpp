﻿#include <iostream>
#include<cmath>
#include <iomanip>
#include<fstream>
#include"Ising mode of function.h"
#include"Ising mode of function.cpp"
//#include"prngcl_ranecu.cl.h"
#include <random>
#include<stdlib.h>
#include<time.h>
#include<ctime>
//#include<thread>

using namespace std;

double randomofjm()
{	
	double r;
	static default_random_engine e(time(0));// it seems has a very different random!
	static uniform_real_distribution<double> u(0, 1);
	r = u(e);
	return  r;
	}


int main (void)
{
	double sum = 0;
	double sum_m = 0;
	double sum_m2 = 0;
	double sum_m4 = 0;
	double sum_e = 0;
	double sum_e2 = 0;
	double point_magnetization = 0;
	//double Binder;
	double magnet4, magnet4_perSpin; 
	magnet4 = magnet4_perSpin = 0;
	double magnet2, magnet2_perSpin;
	magnet2 = magnet2_perSpin = 0;
	double energy2, energy2_perSpin;
	energy2 = energy2_perSpin = 0;
	double Energy, Energy_perSpin;
	Energy = Energy_perSpin = 0;
	double Magnetization, Magnetization_perSpin;
	Magnetization = Magnetization_perSpin = 0;
	int Spins[L][L];
	int InitialSpin = 1;
	ofstream file0;
    file0.open("NEW_L-8_7.25_Ising.txt");
	file0 << "temperature \t <E> \t <E^2> \t <m> \t <m^2> \t <m^4>" << endl;
	//file0 << "## Monte Carlo Simulation for 2D Ising Model with Periodic Boundary conditions" << endl;
	//file0 << "## Algorithm : Metropolis Algorithm" << endl;
	//file0 << "## Random Number type: 	uniform_real_distribution<double> u(0, 1);" << endl;
	//file0 << "## L = " << L << endl;
	//file0 << "## Strength of the Magnetic Field: H = " << H << endl;
	//file0 << "## Total Monte Carlo Time =  " << TotalTime << endl;
	//file0 << "## Relaxation Time =  " << RelaxationTime << endl;
	//file0 << "temperature"<<"\t"<<setw(15)<< " <E>" << "\t" << setw(13) << "<E^2>" << "\t" << setw(28) << " <m>" << "\t" << setw(30) << " <m^2> "<< endl;
	Initialization( InitialSpin, Spins);
	Energy = Energy_total(Spins);
	Magnetization = Magnetization_total(Spins);
	for (double j=0.0; j < 5; j = j + 0.05)
	{
		if (j >= 2.00 && j < 2.95)for (double jj = 0.0; jj < 0.05; jj = jj + 0.01)
		{
			sum = 0.0;
			int  Number = 0;
			sum_m = 0.0;
			sum_m2 = 0.0;
			sum_m4 = 0.0;
			sum_e = 0.0;
			sum_e2 = 0.0;
			point_magnetization = 0.0;
			T = j + jj;
			cout << T << endl;
			for (int k = 0; k <= TotalTime; k++)
			{
				MonteCarloSweep(Spins, Energy, Magnetization, magnet2, energy2, magnet4, T);
				if (k >= RelaxationTime)
				{

					Magnetization_perSpin = Magnetization / (double(L) * L);
					Magnetization_perSpin = fabs(Magnetization_perSpin);//Try it
					sum_m = sum_m + Magnetization_perSpin;
					Energy_perSpin = Energy / (double(L) * L);
					sum_e = sum_e + Energy_perSpin;
					magnet2_perSpin = magnet2 / (double(L) * L * L * L);
					sum_m2 = sum_m2 + magnet2_perSpin;
					energy2_perSpin = energy2 / (double(L) * L * L * L);
					sum_e2 = sum_e2 + energy2_perSpin;
					magnet4_perSpin = magnet4 / (double(L) * L * L * L * L * L * L * L);
					sum_m4 = sum_m4 + magnet4_perSpin;
				}
			}
			//file0 << T << "\t" << setw(30) << (sum_e / 10000.0) << "\t" << setw(30) << (sum_e2 / 10000.0) << "\t" << setw(30) << (sum_m / 10000.0) << "\t " << setw(30) << (sum_m2 / 10000.0) << "\t " << setw(30) << (sum_m4 / 10000.0) << "\t ";
			file0 << T << "\t" << setw(30) << (sum_e / 50000.0) << "\t" << setw(30) << (sum_e2 / 50000.0) << "\t" << setw(30) << (sum_m / 50000.0) << "\t " << setw(30) << (sum_m2 / 50000.0) << "\t " << setw(30) << (sum_m4 / 50000.0) << "\t ";
			file0 << endl;

		}
		else
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
		cout << T << endl;
		for (int k = 0; k < TotalTime; k++)
		{
			MonteCarloSweep(Spins, Energy, Magnetization, magnet2, energy2, magnet4, T);
			if (k >= RelaxationTime)
			{
				Magnetization_perSpin = Magnetization / (double(L) * L);
				Magnetization_perSpin = fabs(Magnetization_perSpin);//no need to have a absolute value.
				sum_m = sum_m + Magnetization_perSpin;
				Energy_perSpin = Energy / (double(L) * L);
				sum_e = sum_e + Energy_perSpin;
				magnet2_perSpin = magnet2 / (double(L) * L * L * L);
				sum_m2 = sum_m2 + magnet2_perSpin;
				energy2_perSpin = energy2 / (double(L) * L * L * L);
				sum_e2 = sum_e2 + energy2_perSpin;
				magnet4_perSpin = magnet4 / (double(L) * L * L * L * L * L * L * L);
				sum_m4 = sum_m4 + magnet4_perSpin;
			}
		}
		file0 << T << "\t" << setw(30) << (sum_e / 50000.0) << "\t" << setw(30) << (sum_e2 / 50000.0) << "\t" << setw(30) << (sum_m / 50000.0) << "\t " << setw(30) << (sum_m2 / 50000.0) << "\t " << setw(30) << (sum_m4 / 50000.0) << "\t ";
		file0 << endl;
		}

	}
	
	file0.close();
	return 0;
}

