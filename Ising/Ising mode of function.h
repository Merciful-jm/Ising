#ifndef _MYfunction__
#define _MYfunction__
#include<iostream>



const double H = 0.0;
const double J = 1.0;
const double mu = 1.0;
const double k_B = 1.0;
const int L = 8;
const int RelaxationTime = 20000;
const int TotalTime = (100000 + RelaxationTime);
//double T = 4;
//default_random_engine e;//生成无符号的随机整数
//0到1（包含）的均匀分布

double randomofjm();

void Initialization(int InitialSpin, int Spins[L][L]);

double Hamiltonian_local(int i, int j, int Spins[L][L]);


double Energy_total(int Spins[L][L]);

double Magnetization_total(int Spins[L][L]);

double EnergyFlip(int i, int j, int Spins[L][L]);

void MonteCarloSweep(int Spins[L][L], double& Energy, double& Magnetzation, double& magnet2, double& energy2, double& magnet4, double& T);

void MonteCarloSweep0(int Spins[L][L], double& Energy, double& Magnetzation);

//void Heat_bath();

static double T;


#endif