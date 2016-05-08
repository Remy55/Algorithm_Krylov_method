// Krylov_method.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "iostream"

using namespace std;

void multiply(long double**, long double**, int);
void initialization(long double**, long double**, int);
void gausMethod(long double**, int);

int main(){

	int n = 4;
	long double** A = new long double*[n];
	long double** Y = new long double*[n];
	for(int i=0; i<n; i++)
	{
		A[i] = new long double[n];
		Y[i] = new long double[n+1];
	}

	initialization(A, Y, n);

	//----------------------TEST--------------------
	//cout << Y[0][1] << "	" << Y[3][4] << endl;
	//--------------------END--TEST-----------------

	multiply(A, Y, n);

	//----------------------TEST--------------------
	//cout << Y[0][1] << "	" << Y[3][4] << endl;
	//--------------------END--TEST-----------------
	
	gausMethod(Y, n);

	cin.get();
	cin.get();
	return 0;
}

void multiply(long double** A,long double** Y, int n){
	long double sum;
	for(int i=1; i<n+1; i++)
		for(int j=0; j<n; j++)
		{
			sum = 0;
			for(int k=0; k<n; k++)
				sum+=A[j][k]*Y[k][i-1];
			Y[j][i] = sum;
		}
	//cout << "Hello :)" << endl;
}

void initialization(long double** A,long double** Y, int n){
	A[0][0] = 6;	A[0][1] = 1.1;	A[0][2] = 0.97;	A[0][3] = 1.24;
	A[1][0] = 1.1;	A[1][1] = 4;	A[1][2] = 1.3;	A[1][3] = 0.16;
	A[2][0] = 0.97;	A[2][1] = 1.3;	A[2][2] = 5;	A[2][3] = 2.1;
	A[3][0] = 1.24;	A[3][1] = 0.16;	A[3][2] = 2.1;	A[3][3] = 7;

	Y[0][0] = 1;	Y[0][1] = 0;	Y[0][2] = 0;	Y[0][3] = 0;	Y[0][4] = 0;
	Y[1][0] = 1;	Y[1][1] = 0;	Y[1][2] = 0;	Y[1][3] = 0;	Y[1][4] = 0;
	Y[2][0] = 1;	Y[2][1] = 0;	Y[2][2] = 0;	Y[2][3] = 0;	Y[2][4] = 0;
	Y[3][0] = 1;	Y[3][1] = 0;	Y[3][2] = 0;	Y[3][3] = 0;	Y[3][4] = 0;
}
void gausMethod(long double** Y, int n){
	long double temp;

	long double* P = new long double[n];
	long double** G = new long double*[n];
	for(int i=0; i<n; i++)
	{
		G[i] = new long double[n+1];
		P[i] = 0;
	}

	for(int i=0; i<n; i++)
		for(int j=0; j<n+1; j++)
		{
			G[i][j] = Y[i][((n-1-j)%(n+1)+n+1)%(n+1)];
			if(j == n) G[i][j] *= (-1);
		}

	//----------------------TEST--------------------
	for(int i=0; i<n; i++)
	{
		for(int j=0; j<n+1; j++)
			cout << G[i][j] << "	";
		cout << endl;
	}
	//--------------------END--TEST-----------------
	
	/*for(int i=0; i<n; i++) //проход по строкам
	{	
		temp = G[i][i];
		for(int j=0; j<n+1; j++) //проход по столбцам
		{
			G[i][j] = G[i][j]/temp; 
			if(i!=j)
			{
				for(int k=i+1; k<n; k++) //проход по строкам внутри столбца
					G[k][j] = G[i][j];
			}
		}
	}*/
	for(int step=0; step < n; step++)
	{
		for(int i=step; i<n; i++)
		{
			temp = G[i][step];
			for(int j=0; j<n+1; j++)
				G[i][j] = G[i][j]/temp;
		}
		for(int i=step+1; i<n; i++)
		{
			for(int j=0; j<n+1; j++)
			{
				G[i][j] -= G[step][j];
			}
		}
	}
	

	//----------------------TEST--------------------
	for(int i=0; i<n; i++)
	{
		for(int j=0; j<n+1; j++)
			cout << G[i][j] << "	";
		cout << endl;
	}
	//--------------------END--TEST-----------------

	for(int i=n-1; i>=0; i--)
	{
		P[i] += G[i][n];

		for(int j = i+1; j < n; j++)
			P[i] -= G[i][j]*P[j];
	}

	//----------------------TEST--------------------
	for(int i=0; i<n; i++)
	{
		cout << P[i] << "	";
		cout << endl;
	}
	//--------------------END--TEST-----------------
}