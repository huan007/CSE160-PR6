#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include "huanAlgo.h"

#define IDX(i,j,n) ((i*n)+j)


void createContiguousArrayDouble(double ***u, int localM, int localN)
{
	int i, j;/*{{{*/
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
	}/*}}}*/
}

void createContiguousArrayInt(int ***u, int localM, int localN)
{
	int i, j;/*{{{*/
	//Allocating contiguous 2d array
	int *tempArray = (int *) malloc(localM * localN * sizeof(int));
	//printf("tempArray: %p\n", tempArray);
	//Creating arrays of  int pointers
	*u = (int **) malloc(localM * sizeof(int *));
	//printf("*u: %p\n", *u);
	for (i = 0; i < localM; i++)
	{
		(*u)[i] = &(tempArray[localN*i]);
		for (j = 0; j < localN; j++)
		{
			(*u)[i][j] = 0;
		}
	}/*}}}*/
}

void printInt(signed int ***array, int localM, int localN)
{
	int i, j;/*{{{*/
	//Begin printing
	for (i = 0; i < localM; i++)
	{
		for (j = 0; j < localN; j++)
		{
			printf("%d ", (*array)[i][j]);
		}
		printf("\n");
	}
	//End printing/*}}}*/
}

void printDouble(double ***array, double localM, double localN)
{
	int i, j;/*{{{*/
	//Begin printing
	for (i = 0; i < localM; i++)
	{
		for (j = 0; j < localN; j++)
		{
			printf("%4.2f\t", (*array)[i][j]);
		}
		printf("\n");
	}
	//End printing/*}}}*/
}

void multiMatrixInt(int **A, int **B, int **C, int M, int P, int N)
{
	int i,j,k;/*{{{*/
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
	}/*}}}*/
}

void multiMatrixDouble(double **A, double **B, double **C, int M, int P, int N)
{
	int i,j,k;/*{{{*/
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
	}/*}}}*/
}

void multiMatrixLowerTransInt(int **A, int **B, int **C, int M, int P, int N)
{
	int i,j,k;/*{{{*/
	for (i = 0; i < M; i++)
	{
		for (j = 0; j < N; j++)
		{
			int sum = 0;
			for (k = 0; k < P; k++)
			{
				//printf("X[%d][%d] = %d\tY[%d][%d] = %d\n", i,k, B[i][k], k, j, C[k][j]);
				sum += B[i][k] * C[j][k];
			}
			//printf("Z[%d][%d] = %d\n", i, j, sum);
			A[i][j] = sum;
		}
	}/*}}}*/
}

void multiMatrixLowerTransDouble(double **A, double **B, double **C, int M, int P, int N)
{
	int i,j,k;/*{{{*/
	for (i = 0; i < M; i++)
	{
		for (j = 0; j < N; j++)
		{
			double sum = 0;
			for (k = 0; k < P; k++)
			{
				sum += B[i][k] * C[j][k];
			}
			A[i][j] = sum;
		}
	}/*}}}*/
}

void sumMatrixInt(int **A, int **B, int M, int N)
{
	int i,j;/*{{{*/
	for (i = 0; i < M; i++)
	{
		for (j = 0; j < N; j++)
		{
			A[i][j] += B[i][j];
		}
	}/*}}}*/
}

void subMatrixInt(int **A, int **B, int M, int N)
{
	int i,j;/*{{{*/
	for (i = 0; i < M; i++)
	{
		for (j = 0; j < N; j++)
		{
			A[i][j] -= B[i][j];
		}
	}/*}}}*/
}

void copyMatrixInt(int **A, int **B, int M, int N)
{
	int i,j;/*{{{*/
	for (i = 0; i < M; i++)
	{
		for (j = 0; j < N; j++)
		{
			A[i][j] = B[i][j];
		}
	}/*}}}*/
}

void zeroMatrixInt(int **A, int M, int N)
{
	int i,j;/*{{{*/
	for (i = 0; i < M; i++)
	{
		for (j = 0; j < N; j++)
		{
			A[i][j] = 0;
		}
	}/*}}}*/
}

void negMatrixInt(int **A, int M, int N)
{
	int i,j;/*{{{*/
	for (i = 0; i < M; i++)
	{
		for (j = 0; j < N; j++)
		{
			signed int temp = -(A[i][j]);
			A[i][j] = temp;
		}
	}/*}}}*/
}

void sumMatrixDouble(double **A, double **B, int M, int N)
{
	int i,j;/*{{{*/
	for (i = 0; i < M; i++)
	{
		for (j = 0; j < N; j++)
		{
			A[i][j] += B[i][j];
		}
	}/*}}}*/
}

void subMatrixDouble(double **A, double **B, int M, int N)
{
	int i,j;/*{{{*/
	for (i = 0; i < M; i++)
	{
		for (j = 0; j < N; j++)
		{
			A[i][j] -= B[i][j];
		}
	}/*}}}*/
}

void copyMatrixDouble(double **A, double **B, int M, int N)
{
	int i,j;/*{{{*/
	for (i = 0; i < M; i++)
	{
		for (j = 0; j < N; j++)
		{
			A[i][j] = B[i][j];
		}
	}/*}}}*/
}

void zeroMatrixDouble(double **A, int M, int N)
{
	int i,j;/*{{{*/
	for (i = 0; i < M; i++)
	{
		for (j = 0; j < N; j++)
		{
			A[i][j] = 0.0f;
		}
	}/*}}}*/
}

void negMatrixDouble(double **A, int M, int N)
{
	int i,j;/*{{{*/
	for (i = 0; i < M; i++)
	{
		for (j = 0; j < N; j++)
		{
			double temp = -(A[i][j]);
			A[i][j] = temp;
		}
	}/*}}}*/
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
	int row, col;/*{{{*/
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
	}/*}}}*/
}

void computeMatrixDouble(double** Z, double** X, double** Y, int M, int N)
{
	int row, col;/*{{{*/
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
	}/*}}}*/
}

void blockCholeskyInt(int ***A, int*** L, int blockCount, int blockSize)
{
	sumMatrixInt(L[IDX(0,0,blockCount)], A[IDX(0,0,blockCount)], blockSize,/*{{{*/
			blockSize);
	int i,j;
	
	//Create a copy of A
	int ***newA = malloc(blockCount * blockCount * sizeof(int**));
	for (i = 0; i < blockCount; i++)
	{
		for (j = 0; j < blockCount; j++)
		{
			createContiguousArrayInt(&(newA[IDX(i,j,blockCount)]), blockSize, blockSize);
			copyMatrixInt(newA[IDX(i,j,blockCount)], A[IDX(i,j,blockCount)], 
				blockSize, blockSize);
		}
	}

	blockInt(newA, L, blockCount, blockSize);
	//Free copy
	for (i = 0; i < blockCount; i++)
	{
		for (j = 0; j < blockCount; j++)
		{
			deleteMatrixInt(newA[IDX(i,j,blockCount)], blockSize, blockSize);
		}
	}
	free(newA);
	/*}}}*/
}

void blockCholeskyDouble(double ***A, double*** L, int blockCount, int blockSize)
{
	printf("blockCholeskyDouble called!\n");
	sumMatrixDouble(L[IDX(0,0,blockCount)], A[IDX(0,0,blockCount)], blockSize,/*{{{*/
			blockSize);
	int i,j;
	
	//Create a copy of A
	double ***newA = malloc(blockCount * blockCount * sizeof(double**));
	for (i = 0; i < blockCount; i++)
	{
		for (j = 0; j < blockCount; j++)
		{
			createContiguousArrayDouble(&(newA[IDX(i,j,blockCount)]), blockSize, blockSize);
			copyMatrixDouble(newA[IDX(i,j,blockCount)], A[IDX(i,j,blockCount)], 
				blockSize, blockSize);
		}
	}

	blockDouble(newA, L, blockCount, blockSize);
	//Free copy
	for (i = 0; i < blockCount; i++)
	{
		for (j = 0; j < blockCount; j++)
		{
			deleteMatrixDouble(newA[IDX(i,j,blockCount)], blockSize, blockSize);
		}
	}
	free(newA);
	/*}}}*/
}

void blockInt(int ***A, int*** L, int blockCount, int blockSize)
{
	if (blockCount == 1)/*{{{*/
	{
		choleskyInt(**L, **A, blockSize);
		return;
	}
	
	int i,j,k;
	int** LT11;

	createContiguousArrayInt(&LT11, blockSize, blockSize);

	//Map top left of the block
	int **A11 = A[IDX(0,0, blockCount)];
	int **L11 = L[IDX(0,0, blockCount)];
	//------STEP 1: Calculate top left------
	choleskyInt(*L11, *A11, blockSize);
	//printMatrixInt(*L11, blockSize);
	//printf("Hello new stack\n");
	//printf("BlockCount: %d\n", blockCount);
	//printf("A11:\n");
	//printInt(&A11, blockSize, blockSize);
	//printf("L11:\n");
	//printInt(&L11, blockSize, blockSize);

	//Inverting L11, we will need it to solve L panel
	for (i = 0; i < blockSize; i++)
	{
		for (j = i; j < blockSize; j++)
		{
			LT11[i][j] = L11[j][i];
		}
	}
		
	//printf("LT11\n");
	//printInt(&LT11, blockSize, blockSize);
	//------STEP 2: Calculate L panel-------
	for (i = 1; i < blockCount; i++)
	{
		computeMatrix(A[IDX(i, 0, blockCount)], L[IDX(i, 0, blockCount)], 
			LT11, blockSize, blockSize);
		//printInt(&(A[IDX(i,0, blockCount)]), blockSize, blockSize);
		//printf("L21[%d]\n", i);
		//printInt(&(L[IDX(i,0, blockCount)]), blockSize, blockSize);
	}
	//------STEP 3: Update A22-------------
	//printf("Update...\n");
	for (i = 1; i < blockCount; i++)
	{
		for (j = 1; j < i+1; j++)
		{
			//printf("L%d0 * LT%d0\n", i, j);
			int ** L21LT21;
			createContiguousArrayInt(&L21LT21, blockSize, blockSize);
			//Calculate L21 * LT21
			multiMatrixLowerTransInt(L21LT21, L[IDX(i,0, blockCount)], L[IDX(j,0, blockCount)],
				blockSize, blockSize, blockSize);
			//printf("L%d0\n", i);
			//printInt(&(L[IDX(i,0, blockCount)]), blockSize, blockSize);
			//printf("LT%d0\n", j);
			//printInt(&(L[IDX(j,0, blockCount)]), blockSize, blockSize);
			//printf("L21LT21\n", j);
			//printInt(&(L21LT21), blockSize, blockSize);
			//Copy A22 to L22
			//sumMatrixInt(L[IDX(i,j,blockCount)], A[IDX(i,j,blockCount)], blockSize,
			//	blockSize);
			//printf("A22\n", j);
			//printInt(&(A[IDX(i,j, blockCount)]), blockSize, blockSize);
			//printf("L22\n", j);
			//printInt(&(L[IDX(i,j, blockCount)]), blockSize, blockSize);
			//Subtract it from A22
			subMatrixInt(A[IDX(i,j, blockCount)], L21LT21, blockSize, blockSize); 
			//printf("A22 (After) with (%d, %d)\n", i, j);
			//printInt(&(A[IDX(i,j, blockCount)]), blockSize, blockSize);
			//printf("\n");
			
			//printf("L22[1][1] (After (%d)(%d)\n", i, j);
			//printInt(&(L[IDX(1,1, blockCount)]), blockSize, blockSize);
			deleteMatrixInt(L21LT21, blockSize, blockSize);
		}
	}
	//------Recursion: Construct new A and L with decremented size-----
	int newBlockCount = blockCount - 1;
	int ***newA = malloc(newBlockCount * newBlockCount * sizeof(int**));
	int ***newL = malloc(newBlockCount * newBlockCount * sizeof(int**));
	
	for (i = 0; i < newBlockCount; i++)
	{
		for (j = 0; j < newBlockCount; j++)
		{
			int newI, newJ;
			newI = i + 1;
			newJ = j + 1;
			//printf("A22 with (%d, %d)\n", newI, newJ);
			//printInt(&(A[IDX(newI,newJ, blockCount)]), blockSize, blockSize);
			newA[IDX(i, j, newBlockCount)] = A[IDX(newI, newJ, blockCount)];
			//printf("newA[%d][%d]\n", i, j);
			//printInt(&(newA[IDX(i,j,newBlockCount)]), blockSize, blockSize);
			newL[IDX(i, j, newBlockCount)] = L[IDX(newI, newJ, blockCount)];
			//printf("newL[%d][%d]\n", i, j);
			//printInt(&(newL[IDX(i,j,newBlockCount)]), blockSize, blockSize);
			//printf("A22 Right after (%d, %d)\n", i, j);
			//printInt(&(A[IDX(2,2, blockCount)]), blockSize, blockSize);
		}
	}
	blockInt(newA, newL, newBlockCount, blockSize);
	free(newA);
	free(newL);
	deleteMatrixInt(LT11, blockSize, blockSize);
	/*}}}*/
}

void blockDouble(double ***A, double*** L, int blockCount, int blockSize)
{
	if (blockCount == 1)/*{{{*/
	{
		cholesky(**L, **A, blockSize);
		return;
	}
	
	int i,j,k;
	double** LT11;

	createContiguousArrayDouble(&LT11, blockSize, blockSize);

	//Map top left of the block
	double **A11 = A[IDX(0,0, blockCount)];
	double **L11 = L[IDX(0,0, blockCount)];
	//------STEP 1: Calculate top left------
	//printf("A11\n");
	//printMatrix(*A11, blockSize);
	//printf("L11\n");
	//printMatrix(*L11, blockSize);
	cholesky(*L11, *A11, blockSize);
	//printMatrix(*L11, blockSize);
	//printf("Hello new stack\n");
	//printf("BlockCount: %d\n", blockCount);
	//printf("A11:\n");
	//printDouble(&A11, blockSize, blockSize);
	//printf("L11:\n");
	//printDouble(&L11, blockSize, blockSize);

	//Inverting L11, we will need it to solve L panel
	for (i = 0; i < blockSize; i++)
	{
		for (j = i; j < blockSize; j++)
		{
			LT11[i][j] = L11[j][i];
		}
	}
		
	//printf("LT11\n");
	//printInt(&LT11, blockSize, blockSize);
	//------STEP 2: Calculate L panel-------
	for (i = 1; i < blockCount; i++)
	{
		computeMatrixDouble(A[IDX(i, 0, blockCount)], L[IDX(i, 0, blockCount)], 
			LT11, blockSize, blockSize);
		//printInt(&(A[IDX(i,0, blockCount)]), blockSize, blockSize);
		//printf("L21[%d]\n", i);
		//printInt(&(L[IDX(i,0, blockCount)]), blockSize, blockSize);
	}
	//------STEP 3: Update A22-------------
	//printf("Update...\n");
	for (i = 1; i < blockCount; i++)
	{
		for (j = 1; j < i+1; j++)
		{
			//printf("L%d0 * LT%d0\n", i, j);
			double ** L21LT21;
			createContiguousArrayDouble(&L21LT21, blockSize, blockSize);
			//Calculate L21 * LT21
			multiMatrixLowerTransDouble(L21LT21, L[IDX(i,0, blockCount)], L[IDX(j,0, blockCount)],
				blockSize, blockSize, blockSize);
			//printf("L%d0\n", i);
			//printInt(&(L[IDX(i,0, blockCount)]), blockSize, blockSize);
			//printf("LT%d0\n", j);
			//printInt(&(L[IDX(j,0, blockCount)]), blockSize, blockSize);
			//printf("L21LT21\n", j);
			//printInt(&(L21LT21), blockSize, blockSize);
			//Copy A22 to L22
			//sumMatrixInt(L[IDX(i,j,blockCount)], A[IDX(i,j,blockCount)], blockSize,
			//	blockSize);
			//printf("A22\n", j);
			//printInt(&(A[IDX(i,j, blockCount)]), blockSize, blockSize);
			//printf("L22\n", j);
			//printInt(&(L[IDX(i,j, blockCount)]), blockSize, blockSize);
			//Subtract it from A22
			subMatrixDouble(A[IDX(i,j, blockCount)], L21LT21, blockSize, blockSize); 
			//printf("A22 (After) with (%d, %d)\n", i, j);
			//printInt(&(A[IDX(i,j, blockCount)]), blockSize, blockSize);
			//printf("\n");
			
			//printf("L22[1][1] (After (%d)(%d)\n", i, j);
			//printInt(&(L[IDX(1,1, blockCount)]), blockSize, blockSize);
			deleteMatrixDouble(L21LT21, blockSize, blockSize);
		}
	}
	//------Recursion: Construct new A and L with decremented size-----
	int newBlockCount = blockCount - 1;
	double ***newA = malloc(newBlockCount * newBlockCount * sizeof(double**));
	double ***newL = malloc(newBlockCount * newBlockCount * sizeof(double**));
	
	for (i = 0; i < newBlockCount; i++)
	{
		for (j = 0; j < newBlockCount; j++)
		{
			int newI, newJ;
			newI = i + 1;
			newJ = j + 1;
			//printf("A22 with (%d, %d)\n", newI, newJ);
			//printInt(&(A[IDX(newI,newJ, blockCount)]), blockSize, blockSize);
			newA[IDX(i, j, newBlockCount)] = A[IDX(newI, newJ, blockCount)];
			//printf("newA[%d][%d]\n", i, j);
			//printInt(&(newA[IDX(i,j,newBlockCount)]), blockSize, blockSize);
			newL[IDX(i, j, newBlockCount)] = L[IDX(newI, newJ, blockCount)];
			//printf("newL[%d][%d]\n", i, j);
			//printInt(&(newL[IDX(i,j,newBlockCount)]), blockSize, blockSize);
			//printf("A22 Right after (%d, %d)\n", i, j);
			//printInt(&(A[IDX(2,2, blockCount)]), blockSize, blockSize);
		}
	}
	blockDouble(newA, newL, newBlockCount, blockSize);
	free(newA);
	free(newL);
	deleteMatrixDouble(LT11, blockSize, blockSize);
	/*}}}*/
}

void printMatrixInt(int *A, int N)
{
	int i,j;/*{{{*/
	for(i = 0; i < N; i++){
		for(j = 0; j < N; j++)
			printf("%d ", A[IDX(i,j,N)]);
		printf("\n");
	}/*}}}*/
}

/* Multiply A*A^T.  
 * double *result - result matrix
 * double * A - source matrix
 * int N - size of matrix (N x N);
 * int lowerT - A is lower triangular
 */
int multTInt(int *result, int *A, int N, int lowerT)
{
	int i,j,k;/*{{{*/
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
	return 0;/*}}}*/
}

/* Compute the Cholesky Decomposition of A 
 * L - NxN result matrix, Lower Triangular L*L^T = A
 * A - NxN symmetric, positive definite matrix A
 * N - size of matrices;
 */
void choleskyInt(int *L, int *A, int N)
{
	int i,j,k;/*{{{*/
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
/*}}}*/
}

void blockToFull(int ***block, int **full, int blockCount, int blockSize)
{
	int blockRow, blockCol, globalRow, globalCol;/*{{{*/
	for (blockRow = 0; blockRow < blockCount; blockRow++)
	{
		for (blockCol = 0; blockCol < blockCount; blockCol++)
		{
			//Offset added to match position in global array
			int offsetRow = blockRow * blockSize;
			int offsetCol = blockCol * blockSize;

			for (globalRow = 0; globalRow < blockSize; globalRow++)
			{
				for (globalCol = 0; globalCol < blockSize; globalCol++)
				{
					full[globalRow+offsetRow][globalCol+offsetCol] = 
						block[IDX(blockRow, blockCol, blockCount)][globalRow][globalCol];
				}
			}
		}
	}/*}}}*/
}

void fullToBlock(int ***block, int **full, int blockCount, int blockSize)
{
	int blockRow, blockCol, globalRow, globalCol;/*{{{*/
	for (blockRow = 0; blockRow < blockCount; blockRow++)
	{
		for (blockCol = 0; blockCol < blockCount; blockCol++)
		{
			//Offset added to match position in global array
			int offsetRow = blockRow * blockSize;
			int offsetCol = blockCol * blockSize;

			for (globalRow = 0; globalRow < blockSize; globalRow++)
			{
				for (globalCol = 0; globalCol < blockSize; globalCol++)
				{
					block[IDX(blockRow, blockCol, blockCount)][globalRow][globalCol] = 
						full[globalRow+offsetRow][globalCol+offsetCol];
				}
			}
		}
	}/*}}}*/
}

void blockToFullDouble(double ***block, double **full, int blockCount, int blockSize)
{
	int blockRow, blockCol, globalRow, globalCol;/*{{{*/
	for (blockRow = 0; blockRow < blockCount; blockRow++)
	{
		for (blockCol = 0; blockCol < blockCount; blockCol++)
		{
			//Offset added to match position in global array
			int offsetRow = blockRow * blockSize;
			int offsetCol = blockCol * blockSize;

			for (globalRow = 0; globalRow < blockSize; globalRow++)
			{
				for (globalCol = 0; globalCol < blockSize; globalCol++)
				{
					full[globalRow+offsetRow][globalCol+offsetCol] = 
						block[IDX(blockRow, blockCol, blockCount)][globalRow][globalCol];
				}
			}
		}
	}/*}}}*/
}

void fullToBlockDouble(double ***block, double **full, int blockCount, int blockSize)
{
	int blockRow, blockCol, globalRow, globalCol;/*{{{*/
	for (blockRow = 0; blockRow < blockCount; blockRow++)
	{
		for (blockCol = 0; blockCol < blockCount; blockCol++)
		{
			//Offset added to match position in global array
			int offsetRow = blockRow * blockSize;
			int offsetCol = blockCol * blockSize;

			for (globalRow = 0; globalRow < blockSize; globalRow++)
			{
				for (globalCol = 0; globalCol < blockSize; globalCol++)
				{
					block[IDX(blockRow, blockCol, blockCount)][globalRow][globalCol] = 
						full[globalRow+offsetRow][globalCol+offsetCol];
				}
			}
		}
	}/*}}}*/
}

void deleteMatrixInt(int **u, int localM, int localN)
{
	//printf("u[0] = %p\n", u[0]);/*{{{*/
	//printf("u = %p\n", u);
	free(u[0]);
	free(u);/*}}}*/
}

void deleteMatrixDouble(double **u, int localM, int localN)
{
	//printf("u[0] = %p\n", u[0]);/*{{{*/
	//printf("u = %p\n", u);
	free(u[0]);
	free(u);/*}}}*/
}
