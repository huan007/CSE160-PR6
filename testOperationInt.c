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
	int **result;
	int **XY;
	int **negY;
	int **upperResult;
	int **fullX;
	int **fullY;
	int **fullZ;
	int **fullResult;
	createContiguousArrayInt(&Z, N, N);
	createContiguousArrayInt(&X, N, N);
	createContiguousArrayInt(&Y, N, N);
	createContiguousArrayInt(&result, M, N);
	createContiguousArrayInt(&XY, N, N);
	createContiguousArrayInt(&negY, N, N);
	createContiguousArrayInt(&upperResult, M, N);
	createContiguousArrayInt(&fullX, N, N);
	createContiguousArrayInt(&fullY, N, N);
	createContiguousArrayInt(&fullZ, N, N);
	createContiguousArrayInt(&fullResult, N, N);



	srand(time(NULL));
	for (count = 0; count < trials; count++)
	{
		printf("Iteration: %d\n", count);
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
		//sumMatrixInt(XY, X, N, N);	/*{{{*/
		//printf("X:\n");
		//printInt(&X, N, N);
		//printf("Y:\n");
		//printInt(&Y, N, N);
		//printf("XY:\n");
		//printInt(&XY, N, N);

		//sumMatrixInt(XY, Y, N, N);
		//printf("XY (After adding Y):\n");
		//printInt(&XY, N, N);
		//sumMatrixInt(negY, Y, N, N);
		//negMatrixInt(negY, N, N);
		//printf("negY:\n");
		//printInt(&negY, N, N);/*}}}*/



		//Multiply out Z
		multiMatrixInt(Z, X, Y, M, N, N);
		multiMatrixLowerTransInt(upperResult, X, X, M, N, N);
		//printf("Z:\n");
		//printInt(&Z, M, N);
		//printf("upperResult:\n");
		//printInt(&upperResult, M, N);
		int ***blockX = malloc(blockCount * blockCount * sizeof(int**));
		int ***blockY = malloc(blockCount * blockCount * sizeof(int**));
		int ***blockZ = malloc(blockCount * blockCount * sizeof(int**));
		int ***blockResult = malloc(blockCount * blockCount * sizeof(int**));
		for (i = 0; i < blockCount; i++)
		{
			for (j = 0; j < blockCount; j++)
			{
				createContiguousArrayInt(&(blockX[IDX(i,j,blockCount)]), blockSize, blockSize);
				createContiguousArrayInt(&(blockY[IDX(i,j,blockCount)]), blockSize, blockSize);
				createContiguousArrayInt(&(blockZ[IDX(i,j,blockCount)]), blockSize, blockSize);
				createContiguousArrayInt(&(blockResult[IDX(i,j,blockCount)]), blockSize, blockSize);
			}
		}

		int blockRow, blockCol;
		int globalRow, globalCol;

		
		fullToBlock(blockX, X, blockCount, blockSize);
		fullToBlock(blockY, Y, blockCount, blockSize);
		fullToBlock(blockZ, Z, blockCount, blockSize);
		fullToBlock(blockResult, fullResult, blockCount, blockSize);
		for (i = 0; i < blockCount; i++)
		{
			for (j = 0; j < blockCount; j++)
			{
				printf("Block (%d,%d)\n", i, j);				
				printInt(&(blockX[IDX(i, j, blockCount)]), blockSize, blockSize);
			}
		}

		printf("Converting block to full...\n");
		blockToFull(blockX, fullX, blockCount, blockSize);
		blockToFull(blockY, fullY, blockCount, blockSize);
		blockToFull(blockZ, fullZ, blockCount, blockSize);
		blockToFull(blockResult, fullResult, blockCount, blockSize);
		printf("fullX\n");
		printInt(&fullX, N, N);
		printf("fullY\n");
		printInt(&fullY, N, N);
		printf("fullZ\n");
		printInt(&fullZ, N, N);

		printf("Calling blockInt...\n");
		blockInt(blockZ, blockResult, blockCount, blockSize);
		blockToFull(blockResult, fullResult, blockCount, blockSize);
		printf("fullX\n");
		printInt(&fullX, N, N);
		printf("fullResult\n");
		printInt(&fullResult, N, N);


		//Compute result
		//computeMatrix(Z, result, Y, M, N);

		//Validation
		for (i = 0; i < M; i++)
		{
			for (j = 0; j < N; j++)
			{
				if (X[i][j] != fullX [i][j] || Y[i][j] != fullY[i][j] || Z[i][j] != fullZ[i][j])
				{
					printf("ERROR: Result is different\n");
					printf("X:\n");
					printInt(&X, M, N);
					printf("Y:\n");
					printInt(&Y, N, N);
					printf("Z:\n");
					printInt(&Z, M, N);
					printf("Result:\n");
					printInt(&result, M, N);
					exit(-1);
				}
			}
		}
	}
	printf("TEST PASSED!\tM: %d\tN: %d\t trials: %d\n", M, N, trials);

	
}
