#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include "huanAlgo.h"

#define IDX(i,j,n) ((i*n)+j)


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

void printInt(signed int ***array, int localM, int localN)
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

void sumMatrixInt(int **A, int **B, int M, int N)
{
	int i,j;
	for (i = 0; i < M; i++)
	{
		for (j = 0; j < N; j++)
		{
			A[i][j] += B[i][j];
		}
	}
}

void subMatrixInt(int **A, int **B, int M, int N)
{
	int i,j;
	for (i = 0; i < M; i++)
	{
		for (j = 0; j < N; j++)
		{
			A[i][j] -= B[i][j];
		}
	}
}

void negMatrixInt(int **A, int M, int N)
{
	int i,j;
	for (i = 0; i < M; i++)
	{
		for (j = 0; j < N; j++)
		{
			signed int temp = -(A[i][j]);
			A[i][j] = temp;
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
	long double top, bottom;

	//Go columns by columns because if we have column 1, we can solve for column
	//2 and so on.
	for (col = 0; col < N; col++)
	{
		//Loop through each row to solve for X
		for (row = 0; row < M; row++)
		{
			top = Z[row][col];	
			long double sum = 0.0;

			//Accuminlating terms on top
			for (i = 0; i < col; i++)
			{
				sum = sum + ( (long double) X[row][i] * (long double) Y[i][col]);
				top -= ( (long double) X[row][i] * (long double) Y[i][col]);	
			}
			long double temp = (long double) Z[row][col] - sum;
			X[row][col] = (long double) temp / (long double) Y[col][col];
			//printf("temp: \t%6.20f\n", temp);
			//printf("top: \t%6.20f\n", top);
			//printf("X[%d][%d] = %d\n", row, col, X[row][col]);
		}
	}
}

void blockInt(int ***A, int*** L, int blockCount, int blockSize)
{
	if (blockCount == 1)
		choleskyInt(**L, **A, blockSize);
	
	int i,j,k;
	int*** A21;
	int*** L21;
	int** LT11;

	A21 = (int***) malloc ( (blockCount - 1) * sizeof(int**) );
	L21 = (int***) malloc ( (blockCount - 1) * sizeof(int**) );
	createContiguousArrayInt(&LT11, blockSize, blockSize);

	//Map top left of the block
	int **A11 = A[IDX(0,0, blockCount)];
	int **L11 = L[IDX(0,0, blockCount)];
	//------STEP 1: Calculate top left------
	choleskyInt(*L11, *A11, blockSize);

	//Inverting L11
	for (i = 0; i < blockSize; i++)
	{
		for (j = i; j < blockSize; j++)
		{
			LT11[i][j] = L11[j][i];
		}
	}
		
	//------STEP 2: Calculate L panel-------
	for (i = 1; i < blockCount; i++)
	{
		computeMatrix(A[IDX(i, 0, blockCount)], L[IDX(i, 0, blockCount)], 
			LT11, blockSize, blockSize);
	}
	//------STEP 3: Update A22-------------
}

void printMatrixInt(int *A, int N)
{
	int i,j;
	for(i = 0; i < N; i++){
		for(j = 0; j < N; j++)
			printf("%d ", A[IDX(i,j,N)]);
		printf("\n");
	}
}

/* Multiply A*A^T.  
 * double *result - result matrix
 * double * A - source matrix
 * int N - size of matrix (N x N);
 * int lowerT - A is lower triangular
 */
int multTInt(int *result, int *A, int N, int lowerT)
{
	int i,j,k;
	bzero(result, N*N*sizeof(int));
	for(i = 0; i < N; i++)
	{
		/* Result is symmetric, just compute upper triangle */
		for(j = i; j < N; j++) 
		{
			int sum = 0.0;
			//printf("Start sum [%d][%d]\n", i, j);
			/* if A is lower Triangular don't multiply zeroes */
			for(k = 0; k < (!lowerT ? N : j+1) ; k++)
			{
				//printf("%3.6f\t %3.6f\n", A[IDX(i,k,N)], A[IDX(j,k,N)]);
				sum += A[IDX(i,k,N)] * A[IDX(j,k,N)];
			}
			result[IDX(i,j,N)] = sum;
			result[IDX(j,i,N)] = sum; /*enforce symmetry */
		}
		//printf("Outside\n");
	}
	//printMatrix(result, N);
	return 0;
}

/* Compute the Cholesky Decomposition of A 
 * L - NxN result matrix, Lower Triangular L*L^T = A
 * A - NxN symmetric, positive definite matrix A
 * N - size of matrices;
 */
void choleskyInt(int *L, int *A, int N)
{
	int i,j,k;
	bzero(L,N*N*sizeof(int));
	int temp;
	for (i = 0; i < N; i++){
		for (j = 0; j < (i+1); j++) {
			temp = 0;
			/* Inner product of ith row of L, jth row of L */
			for (k = 0; k < j; k++)
				temp += L[IDX(i,k,N)] * L[IDX(j,k,N)];
			if (i == j)
				L[IDX(i,j,N)] = sqrt(A[IDX(i,i,N)] - temp);
			else {
				L[IDX(i,j,N)] = (A[IDX(i,j,N)] - temp)/ L[IDX(j,j,N)];
			}
		  }
	}

}
