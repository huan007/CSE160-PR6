#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include "huanAlgo.h"
#include "choleskyCommon.h"
#include "cs160validate.h"

#ifdef _OPENMP
#include <omp.h>
#define NUMARGS 4
#else
#define NUMARGS 3
#endif

#define MAXNUM 9
#define MINNUM 1995
#define FACTOR 2000
#define THRESH 1e-13
#define SCALE 100.0
#define uSECtoSEC 1.0E-6
//#define GEN_INT() ((rand() % MAXNUM) + MINNUM)
#define GEN_INT() ((drand48() * FACTOR) + MINNUM)
#define IDX(i,j,n) ((i*n)+j)

void usage()
{
#ifdef _OPENMP
	printf("usage: blockCholeskyMP <K> <blksize> <nthread>\n");
#else
	printf("usage: blockCholesky <K> <blksize>\n");
#endif
	exit(-1);
}
int main(int argc, char** argv)
{
	printf("# of arguments: %d\n", argc);
	if (argc < NUMARGS)
		usage();

	int N;
	int blockSize = atoi(argv[1]);
	int blockCount = atoi(argv[2]);
	int trials = 1;
#ifdef _OPENMP
	thread_count = atoi(argv[3]);
#else
	thread_count = 1;
#endif
	int i, j, k, l, m, n;
	int count = 0;

	N = blockSize * blockCount;
	double **Z; 
	double **X; 
	double **Y;
	double **fullResult;
	//createContiguousArrayDouble(&Z, N, N);
	//createContiguousArrayDouble(&X, N, N);
	//createContiguousArrayDouble(&Y, N, N);
	createContiguousArrayDouble(&fullResult, N, N);
	double time_init = 0;
	double time_calc = 0;
	double time_veri = 0;
	double avg_init, avg_calc, avg_veri;
	double **A;
	createContiguousArrayDouble(&A, N, N);

	srand(1);
	srand48(time(NULL));
	printf("Start testBlockDouble SIDAAA!\n");
	for (count = 0; count < trials; count++)
	{
		double start, end;
		double totalTime;
		printf("Iteration: %d\n", count);
		//printf("Setting up...\n");
		//Generate randum integers in X;
		//for (i = 0; i < M; i++)
		//{
		//	for(j = 0; j < N; j++)
		//	{
		//		X[i][j] = GEN_INT();
		//	}
		//}

		start = get_clock();
		//Generate randum integers in Y;
		//for (i = 0; i < N; i++)
		//{
		//	for(j = 0; j < i + 1; j++)
		//	{
		//		double temp = GEN_INT();
		//		Y[j][i] = temp;
		//		X[i][j] = temp;
		//	}
		//}

		//Multiply out Z
		//multiMatrixDouble(Z, X, Y, N, N, N);
		//printf("Z:\n");
		//printInt(&Z, M, N);
		init_array(N,1,*A);
		//printf("A\n");
		////printMatrix(A, N);
		//printDouble(&A, N, N);
		//printf("upperResult:\n");
		//printInt(&upperResult, M, N);
		//int ***blockX = malloc(blockCount * blockCount * sizeof(int**));
		//int ***blockY = malloc(blockCount * blockCount * sizeof(int**));
		printf("Allocating block variables\n");
		//double ***blockZ = malloc(blockCount * blockCount * sizeof(double**));
		double ***blockA = malloc(blockCount * blockCount * sizeof(double**));
		double ***blockResult = malloc(blockCount * blockCount * sizeof(double**));
		//Allocating blocks
		for (i = 0; i < blockCount; i++)
		{
			for (j = 0; j < blockCount; j++)
			{
				//createContiguousArrayInt(&(blockX[IDX(i,j,blockCount)]), blockSize, blockSize);
				//createContiguousArrayInt(&(blockY[IDX(i,j,blockCount)]), blockSize, blockSize);
				//createContiguousArrayDouble(&(blockZ[IDX(i,j,blockCount)]), blockSize, blockSize);
				createContiguousArrayDouble(&(blockA[IDX(i,j,blockCount)]), blockSize, blockSize);
				createContiguousArrayDouble(&(blockResult[IDX(i,j,blockCount)]), blockSize, blockSize);
			}
		}

		printf("Converting full to block\n");
		//fullToBlockDouble(blockZ, Z, blockCount, blockSize);
		fullToBlockDouble(blockA, A, blockCount, blockSize);
		//fullToBlock(blockResult, fullResult, blockCount, blockSize);

		//printf("Converting block to full...\n");
		//blockToFull(blockX, fullX, blockCount, blockSize);
		//blockToFull(blockY, fullY, blockCount, blockSize);
		//blockToFull(blockZ, fullZ, blockCount, blockSize);
		//blockToFull(blockResult, fullResult, blockCount, blockSize);
		//printf("fullX\n");
		//printInt(&fullX, N, N);
		//printf("fullY\n");
		//printInt(&fullY, N, N);
		
		//printf("fullZ\n");
		//printDouble(&Z, N, N);

		//printf("Calling blockInt...\n");
		end = get_clock();
		totalTime = end - start;
		time_init += totalTime;

		//Cholesky using serial algorith
		//double *L = (double *)malloc(N*N *sizeof(double));
		//choleskySingle(L, *A, N);
		//printf("L (serial cholesky)\n");
		//printMatrix(L, N);

		printf("Calling blockCholesky\n");
		start = get_clock();
		blockCholeskyDouble(blockA, blockResult, blockCount, blockSize);
		end = get_clock();
		totalTime = end - start;
		time_calc += totalTime;
		//printf("*TIME* (Calculation) Time taken: %6.4f\n", totalTime);
		blockToFullDouble(blockResult, fullResult, blockCount, blockSize);

		//blockToFull(blockZ, fullZ, blockCount, blockSize);
		//printf("fullZ\n");
		//printInt(&fullZ, N, N);
		//printf("fullX\n");
		//printInt(&fullX, N, N);
		//printf("fullResult\n");
		//printDouble(&fullResult, N, N);
		start = get_clock();
		int badCount = validate(*A, *fullResult, N, THRESH); 
		end = get_clock();
		totalTime = end - start;
		time_veri += totalTime;
		//printf("*TIME* (Verification) Time taken: %6.4f\n", totalTime);
		printf("Bad Count = %d\n", badCount);
		cs160validate(*A, *fullResult, N, THRESH); 
		//if (badCount > 0)
		//	exit(-1);

		//Validation
		//printf("Validating...\n");
		//for (i = 0; i < N; i++)
		//{
		//	for (j = 0; j < i+1; j++)
		//	{
		//		double err = abs(X[i][j] - fullResult[i][j]) / X[i][j];
		//		if (err > THRESH)
		//		{
		//			printf("ERROR: Result is different\n");
		//			printf("X[%d][%d] = \t\t%5.16f\n", i,j,X[i][j]);
		//			printf("result[%d][%d] = \t%5.16f\n", i,j,fullResult[i][j]);
		//			printf("Error: %5.16e\n", err);
		//		}
		//	}
		//}

		for (i = 0; i < blockCount; i++)
		{
			for (j = 0; j < blockCount; j++)
			{
				deleteMatrixDouble(blockA[IDX(i,j,blockCount)], blockSize, blockSize);
				deleteMatrixDouble(blockResult[IDX(i,j,blockCount)], blockSize, blockSize);
			}
		}
		free(blockA);
		free(blockResult);
	}
	printf("TEST PASSED after %d trials\n", trials);
	printf("*LOG* blockSize: %d\tblockCount: %d\tN: %d", blockSize, blockCount, N);
	printf("\tInit:\t %6.4f", time_init / trials);
	printf("\tCalc:\t %6.4f", time_calc / trials);
	printf("\tVeri:\t %6.4f\n", time_veri / trials);
	//deleteMatrixDouble(Z, N, N);
	//deleteMatrixDouble(X, N, N);
	//deleteMatrixDouble(Y, N, N);
	deleteMatrixDouble(A, N, N);
	deleteMatrixDouble(fullResult, N, N);

	exit(0);	
}
