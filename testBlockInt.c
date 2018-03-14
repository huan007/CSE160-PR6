#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include "huanAlgo.h"


#define MAXNUM 9
#define MINNUM 1
#define GEN_INT() ((rand() % MAXNUM) + MINNUM)
#define IDX(i,j,n) ((i*n)+j)

void usage()
{
	printf("usage: testAlgo <M> <N> <size> <count> <trials>\n");
	exit(-1);
}
int main(int argc, char** argv)
{
	if (argc < 6)
		usage();

	int M = atoi(argv[1]);
	int N = atoi(argv[2]);
	int blockSize = atoi(argv[3]);
	int blockCount = atoi(argv[4]);
	int trials = atoi(argv[5]);
	int i, j, k, l, m, n;
	int count = 0;

	N = blockSize * blockCount;
	M = N;
	int **Z; 
	int **X; 
	int **Y;
	int **fullResult;
	createContiguousArrayInt(&Z, N, N);
	createContiguousArrayInt(&X, N, N);
	createContiguousArrayInt(&Y, N, N);
	createContiguousArrayInt(&fullResult, N, N);

	srand(1);
	for (count = 0; count < trials; count++)
	{
		printf("Iteration: %d\n", count);
		printf("Setting up...\n");
		//Generate randum integers in X;
		//for (i = 0; i < M; i++)
		//{
		//	for(j = 0; j < N; j++)
		//	{
		//		X[i][j] = GEN_INT();
		//	}
		//}

		//Generate randum integers in Y;
		for (i = 0; i < N; i++)
		{
			for(j = 0; j < i + 1; j++)
			{
				int temp = GEN_INT();
				Y[j][i] = temp;
				X[i][j] = temp;
			}
		}



		//Multiply out Z
		multiMatrixInt(Z, X, Y, M, N, N);
		//printf("Z:\n");
		//printInt(&Z, M, N);
		//printf("upperResult:\n");
		//printInt(&upperResult, M, N);
		//int ***blockX = malloc(blockCount * blockCount * sizeof(int**));
		//int ***blockY = malloc(blockCount * blockCount * sizeof(int**));
		int ***blockZ = malloc(blockCount * blockCount * sizeof(int**));
		int ***blockResult = malloc(blockCount * blockCount * sizeof(int**));
		for (i = 0; i < blockCount; i++)
		{
			for (j = 0; j < blockCount; j++)
			{
				//createContiguousArrayInt(&(blockX[IDX(i,j,blockCount)]), blockSize, blockSize);
				//createContiguousArrayInt(&(blockY[IDX(i,j,blockCount)]), blockSize, blockSize);
				createContiguousArrayInt(&(blockZ[IDX(i,j,blockCount)]), blockSize, blockSize);
				createContiguousArrayInt(&(blockResult[IDX(i,j,blockCount)]), blockSize, blockSize);
			}
		}

		//fullToBlock(blockX, X, blockCount, blockSize);
		//fullToBlock(blockY, Y, blockCount, blockSize);
		fullToBlock(blockZ, Z, blockCount, blockSize);
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
		//printInt(&fullZ, N, N);

		//printf("Calling blockInt...\n");
		printf("Calculating...\n");
		blockCholeskyInt(blockZ, blockResult, blockCount, blockSize);
		blockToFull(blockResult, fullResult, blockCount, blockSize);
		//blockToFull(blockZ, fullZ, blockCount, blockSize);
		//printf("fullZ\n");
		//printInt(&fullZ, N, N);
		//printf("fullX\n");
		//printInt(&fullX, N, N);
		//printf("fullResult\n");
		//printInt(&fullResult, N, N);

		//Validation
		printf("Validating...\n");
		for (i = 0; i < M; i++)
		{
			for (j = 0; j < N; j++)
			{
				if (X[i][j] != fullResult[i][j])
				{
					printf("ERROR: Result is different\n");
					printf("X:\n");
					printInt(&X, M, N);
					printf("Y:\n");
					printInt(&Y, N, N);
					printf("Z:\n");
					printInt(&Z, M, N);
					exit(-1);
				}
			}
		}

		for (i = 0; i < blockCount; i++)
		{
			for (j = 0; j < blockCount; j++)
			{
				deleteMatrixInt(blockZ[IDX(i,j,blockCount)], blockSize, blockSize);
				deleteMatrixInt(blockResult[IDX(i,j,blockCount)], blockSize, blockSize);
			}
		}
		free(blockZ);
		free(blockResult);
	}
	printf("TEST PASSED!\tM: %d\tN: %d\t trials: %d\n", M, N, trials);
	deleteMatrixInt(Z, N, N);
	deleteMatrixInt(X, N, N);
	deleteMatrixInt(Y, N, N);
	deleteMatrixInt(fullResult, N, N);

	
}
