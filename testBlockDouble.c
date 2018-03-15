#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include "huanAlgo.h"
#include "cholesky.c"


#define MAXNUM 9
#define MINNUM 1
#define FACTOR 100
#define THRESH 1e-14
#define SCALE 100.0
#define uSECtoSEC 1.0E-6
//#define GEN_INT() ((rand() % MAXNUM) + MINNUM)
#define GEN_INT() ((drand48() * FACTOR) + MINNUM)
#define IDX(i,j,n) ((i*n)+j)

void usage()
{
	printf("usage: testAlgo <M> <N> <size> <count> <trials>\n");
	exit(-1);
}
int main(int argc, char** argv)
{
	if (argc < 4)
		usage();

	int N;
	int blockSize = atoi(argv[1]);
	int blockCount = atoi(argv[2]);
	int trials = atoi(argv[3]);
	int i, j, k, l, m, n;
	int count = 0;

	N = blockSize * blockCount;
	double **Z; 
	double **X; 
	double **Y;
	double **fullResult;
	createContiguousArrayDouble(&Z, N, N);
	createContiguousArrayDouble(&X, N, N);
	createContiguousArrayDouble(&Y, N, N);
	createContiguousArrayDouble(&fullResult, N, N);
	double time_init = 0;
	double time_calc = 0;
	double time_veri = 0;
	double avg_init, avg_calc, avg_veri;

	srand(1);
	srand48(1);
	printf("Start testBlockDouble!\n");
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
		for (i = 0; i < N; i++)
		{
			for(j = 0; j < i + 1; j++)
			{
				double temp = GEN_INT();
				Y[j][i] = temp;
				X[i][j] = temp;
			}
		}



		//Multiply out Z
		multiMatrixDouble(Z, X, Y, N, N, N);
		//printf("Z:\n");
		//printInt(&Z, M, N);
		//printf("upperResult:\n");
		//printInt(&upperResult, M, N);
		//int ***blockX = malloc(blockCount * blockCount * sizeof(int**));
		//int ***blockY = malloc(blockCount * blockCount * sizeof(int**));
		double ***blockZ = malloc(blockCount * blockCount * sizeof(double**));
		double ***blockResult = malloc(blockCount * blockCount * sizeof(double**));
		//Allocating blocks
		for (i = 0; i < blockCount; i++)
		{
			for (j = 0; j < blockCount; j++)
			{
				//createContiguousArrayInt(&(blockX[IDX(i,j,blockCount)]), blockSize, blockSize);
				//createContiguousArrayInt(&(blockY[IDX(i,j,blockCount)]), blockSize, blockSize);
				createContiguousArrayDouble(&(blockZ[IDX(i,j,blockCount)]), blockSize, blockSize);
				createContiguousArrayDouble(&(blockResult[IDX(i,j,blockCount)]), blockSize, blockSize);
			}
		}

		//fullToBlock(blockX, X, blockCount, blockSize);
		//fullToBlock(blockY, Y, blockCount, blockSize);
		fullToBlockDouble(blockZ, Z, blockCount, blockSize);
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
		//printf("*TIME* (Initialization) Time taken: %6.4f\n", totalTime);
		//printf("Calculating...\n");
		start = get_clock();
		blockCholeskyDouble(blockZ, blockResult, blockCount, blockSize);
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
		int badCount = validate(*Z, *X, N, THRESH); 
		end = get_clock();
		totalTime = end - start;
		time_veri += totalTime;
		//printf("*TIME* (Verification) Time taken: %6.4f\n", totalTime);
		printf("Bad Count = %d\n", badCount);
		if (badCount > 0)
			exit(-1);

		//Validation
		//printf("Validating...\n");
		//for (i = 0; i < M; i++)
		//{
		//	for (j = 0; j < N; j++)
		//	{
		//		if (X[i][j] != fullResult[i][j])
		//		{
		//			printf("ERROR: Result is different\n");
		//			printf("X:\n");
		//			printDouble(&X, M, N);
		//			printf("Y:\n");
		//			printDouble(&Y, N, N);
		//			printf("Z:\n");
		//			printDouble(&Z, M, N);
		//			exit(-1);
		//		}
		//	}
		//}

		for (i = 0; i < blockCount; i++)
		{
			for (j = 0; j < blockCount; j++)
			{
				deleteMatrixDouble(blockZ[IDX(i,j,blockCount)], blockSize, blockSize);
				deleteMatrixDouble(blockResult[IDX(i,j,blockCount)], blockSize, blockSize);
			}
		}
		free(blockZ);
		free(blockResult);
	}
	printf("TEST PASSED after %d trials\n", trials);
	printf("*LOG* blockSize: %d\tblockCount: %d\tN: %d", blockSize, blockCount, N);
	printf("\tInit:\t %6.4f", time_init / trials);
	printf("\tCalc:\t %6.4f", time_calc / trials);
	printf("\tVeri:\t %6.4f\n", time_veri / trials);
	deleteMatrixDouble(Z, N, N);
	deleteMatrixDouble(X, N, N);
	deleteMatrixDouble(Y, N, N);
	deleteMatrixDouble(fullResult, N, N);

	exit(0);	
}
