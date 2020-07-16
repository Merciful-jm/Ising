#include"Ising mode of function.h"
#include<iostream>
#include <random>



void Initialization( int InitialSpin,int Spins[L][L])
{
	for (int i = 0; i < L; i++)
	{
		for (int j = 0; j < L; j++)
		{
			Spins[i][j] = InitialSpin;
			/*if (randomofjm() < 0.5)
			{
				Spins[i][j] = InitialSpin;
			}
			else
			{
				Spins[i][j] = -InitialSpin;
			}*/
		}
	}
}

double Hamiltonian_local(int i, int j, int Spins[L][L])
{
	int m, n, p, q;
	double hhh = 0.0;
	if (i == 0)
	{
		m = L - 1;
		n = 1;
	}
	else if (i==L-1)
	{
		m = L - 2;
		n = 0;
	}
	else
	{
		m = i - 1;//normaly
		n = i + 1;//normaly
	}
	if (j==0)
	{
		p = L - 1;/////////Finally find it!
		q = 1;
	}
	else if (j==L-1)
	{
		p = L - 2;
		q = 0;
	}
	else
	{
		p = j - 1;//normaly
		q = j + 1;//normaly
	}
	hhh=-Spins[i][j] * (J * (Spins[m][j]  + Spins[n][j] + Spins[i][p] + Spins[i][q]) + mu * H);
	return hhh; //cancled the "+ mu * H" term
}

double Energy_total(int Spins[L][L])
{
	double Sum = 0.0;
	for (int i = 0; i < L; i++)
	{
		for (int j = 0; j < L; j++)
			Sum = Sum + Hamiltonian_local(i, j, Spins);
	}
	return Sum / 2.0;
}


double Magnetization_total(int Spins[L][L])
{
	double Sum = 0.0;
	for (int i = 0; i < L; i++)
	{
		for (int j = 0; j < L; j++)
			Sum = Sum + Spins[i][j];
	}
	return Sum;
}

double EnergyFlip(int i, int j, int Spins[L][L])
{
	double E1, E2;
	E1 = Hamiltonian_local( i, j, Spins);
	Spins[i][j] = -Spins[i][j];
	E2 = Hamiltonian_local(i, j, Spins);
	Spins[i][j] = -Spins[i][j];
	return E2 - E1;
}

//void MonteCarloSweep0(int Spins[L][L], double& Energy, double& Magnetzation)
//{
//	double Energy_Flip;
//	double BoltzmannFactor;
//	double RandomNum;
//	for (int i = 0; i < L; i++)
//	{
//		for (int j = 0; j < L; j++)
//		{
//			Energy_Flip = EnergyFlip(i, j, Spins);
//			if (Energy_Flip <= 0)
//			{
//				Spins[i][j] = -Spins[i][j];
//				Energy = Energy + Energy_Flip;
//				Magnetzation = Magnetzation + 2.0 * Spins[i][j];	
//			}
//			else
//			{
//				BoltzmannFactor = exp(-Energy_Flip / (k_B * 4.0));
//				RandomNum = randomofjm();
//				if (RandomNum <= BoltzmannFactor)
//				{
//					Spins[i][j] = -Spins[i][j];
//					Energy = Energy + Energy_Flip;
//					Magnetzation = Magnetzation + 2.0 * Spins[i][j];					
//				}
//			}
//		}
//	}
//}



void MonteCarloSweep(int Spins[L][L], double& Energy, double& Magnetzation, double& magnet2, double& energy2, double& magnet4, double& T)
{

	double Energy_Flip;
	double BoltzmannFactor;
	double RandomNum;
	for (int i = 0; i < L; i++)
	{
		for (int j = 0; j < L; j++)
		{
			Energy_Flip = EnergyFlip(i, j, Spins);
			if (Energy_Flip <= 0)
			{
				Spins[i][j] = -Spins[i][j];
				Energy = Energy + Energy_Flip;
				Magnetzation = Magnetzation + 2.0 * Spins[i][j];
				magnet2 = (Magnetzation * Magnetzation);
				magnet4 = (Magnetzation * Magnetzation * Magnetzation * Magnetzation);
				energy2 = (Energy * Energy);
			}
			else
			{
				BoltzmannFactor = exp(-Energy_Flip / (k_B * T));
				RandomNum = randomofjm();
				if (RandomNum <= BoltzmannFactor)
				{
					Spins[i][j] = -Spins[i][j];
					Energy = Energy + Energy_Flip;
					Magnetzation = Magnetzation + 2.0 * Spins[i][j];
					magnet2 = (Magnetzation * Magnetzation);
					magnet4 = (Magnetzation * Magnetzation * Magnetzation * Magnetzation);
					energy2 = (Energy * Energy);
				}
			}
		}
	}
}



