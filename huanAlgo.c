#include <stdlib.h>
#include <stdio.h>
#include <math.h>


void createContiguousArrayDouble(double ***u, int localM, int localN)
{
	int i, j;
	//Allocating contiguous 2d array
	double *tempArray = (double *) malloc(localM * localN * sizeof(double));
	//Creating arrays of  double pointers
	*u = (double **) malloc(localM * sizeof(double *));
	for (i = 0; i < localM; i++)
	{
		(*u)[i] = &(tempArray[localN*i]);
		for (j = 0; j < localN; j++)
		{
			(*u)[i][j] = 0;
		}
	}
}

void createContiguousArrayInt(int ***u, int localM, int localN)
{
	int i, j;
	//Allocating contiguous 2d array
	int *tempArray = (int *) malloc(localM * localN * sizeof(int));
	//Creating arrays of  int pointers
	*u = (int **) malloc(localM * sizeof(int *));
	for (i = 0; i < localM; i++)
	{
		(*u)[i] = &(tempArray[localN*i]);
		for (j = 0; j < localN; j++)
		{
			(*u)[i][j] = 0;
		}
	}
}

void printInt(int ***array, int localM, int localN)
{
	int i, j;
	//Begin printing
	for (i = 0; i < localM; i++)
	{
		for (j = 0; j < localN; j++)
		{
			printf("%d ", (*array)[i][j]);
		}
		printf("\n");
	}
	//End printing
}

void printDouble(double ***array, double localM, double localN)
{
	int i, j;
	//Begin printing
	for (i = 0; i < localM; i++)
	{
		for (j = 0; j < localN; j++)
		{
			printf("%4.20f\t", (*array)[i][j]);
		}
		printf("\n");
	}
	//End printing
}

void multiMatrixInt(int **A, int **B, int **C, int M, int P, int N)
{
	int i,j,k;
	for (i = 0; i < M; i++)
	{
		for (j = 0; j < N; j++)
		{
			int sum = 0;
			for (k = 0; k < P; k++)
			{
				//printf("X[%d][%d] = %d\tY[%d][%d] = %d\n", i,k, B[i][k], k, j, C[k][j]);
				sum += B[i][k] * C[k][j];
			}
			//printf("Z[%d][%d] = %d\n", i, j, sum);
			A[i][j] = sum;
		}
	}
}

void multiMatrixDouble(double **A, double **B, double **C, int M, int P, int N)
{
	int i,j,k;
	for (i = 0; i < M; i++)
	{
		for (j = 0; j < N; j++)
		{
			double sum = 0.0;
			for (k = 0; k < P; k++)
			{
				//printf("X[%d][%d] = %d\tY[%d][%d] = %d\n", i,k, B[i][k], k, j, C[k][j]);
				sum += (double ) B[i][k] * (double) C[k][j];
			}
			//printf("Z[%d][%d] = %d\n", i, j, sum);
			A[i][j] = sum;
		}
	}
}

/*
 * Compute X given Z and Y. Z is the original matrix, Y is a top triangle of a
 * decomposed cholesky LU factorization of Z. Assuming that we have all the
 * correct values of Z and Y
 *
 * ASSUME: that Y is the upper half, thus the lower half left is all 0s
 */
void computeMatrix(int** Z, int** X, int** Y, int M, int N)
{
	int row, col;
	int i, j;
	int top, bottom;

	//Go columns by columns because if we have column 1, we can solve for column
	//2 and so on.
	for (col = 0; col < N; col++)
	{
		//Loop through each row to solve for X
		for (row = 0; row < M; row++)
		{
			top = Z[row][col];	

			//Accuminlating terms on top
			for (i = 0; i < col; i++)
			{
				top -= (X[row][i] * Y[i][col]);	
			}
			X[row][col] = top / Y[col][col];
			//printf("X[%d][%d] = %d\n", row, col, X[row][col]);
		}
	}
}

void computeMatrixDouble(double** Z, double** X, double** Y, int M, int N)
{
	int row, col;
	int i, j;
	double top, bottom;

	//Go columns by columns because if we have column 1, we can solve for column
	//2 and so on.
	for (col = 0; col < N; col++)
	{
		//Loop through each row to solve for X
		for (row = 0; row < M; row++)
		{
			top = Z[row][col];	
			double sum = 0.0;

			//Accuminlating terms on top
			for (i = 0; i < col; i++)
			{
				sum = sum + ( (double) X[row][i] * (double) Y[i][col]);
				top -= ( (double) X[row][i] * (double) Y[i][col]);	
			}
			double temp = Z[row][col] - sum;
			X[row][col] = (double) temp / (double) Y[col][col];
			//printf("temp: \t%6.20f\n", temp);
			//printf("top: \t%6.20f\n", top);
			//printf("X[%d][%d] = %d\n", row, col, X[row][col]);
		}
	}
}
