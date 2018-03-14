#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include "huanAlgo.h"


#define MAXNUM 1000
#define MINNUM 1
#define GEN_INT() ((rand() % MAXNUM) + MINNUM)

void usage()
{
	printf("usage: testAlgo <M> <N> <trials>\n");
	exit(-1);
}
int main(int argc, char** argv)
{
	if (argc < 4)
		usage();

	int M = atoi(argv[1]);
	int N = atoi(argv[2]);
	int trials = atoi(argv[3]);
	int i, j, k;
	int count = 0;

	int **Z; 
	int **X; 
	int **Y;
	int **result;
	printf("Z\n");
	createContiguousArrayInt(&Z, M, N);
	printf("X\n");
	createContiguousArrayInt(&X, M, N);
	printf("Y\n");
	createContiguousArrayInt(&Y, N, N);
	printf("result\n");
	createContiguousArrayInt(&result, M, N);

	deleteMatrixInt(Z, M, N);
	deleteMatrixInt(X, M, N);
	deleteMatrixInt(Y, M, N);
	deleteMatrixInt(result, M, N);

	//srand(time(NULL));
	//for (count = 0; count < trials; count++)
	//{
	//	printf("Iteration: %d\n", count);
	//	//Generate randum integers in X;
	//	for (i = 0; i < M; i++)
	//	{
	//		for(j = 0; j < N; j++)
	//		{
	//			X[i][j] = GEN_INT();
	//		}
	//	}

	//	//Generate randum integers in Y;
	//	for (i = 0; i < N; i++)
	//	{
	//		for(j = 0; j < i + 1; j++)
	//		{
	//			Y[j][i] = GEN_INT();
	//		}
	//	}

	//	//Multiply out Z
	//	multiMatrixInt(Z, X, Y, M, N, N);
	//	//Compute result
	//	computeMatrix(Z, result, Y, M, N);

	//	//Validation
	//	for (i = 0; i < M; i++)
	//	{
	//		for (j = 0; j < N; j++)
	//		{
	//			if (X[i][j] != result [i][j])
	//			{
	//				printf("ERROR: Result is different\n");
	//				printf("X:\n");
	//				printInt(&X, M, N);
	//				printf("Y:\n");
	//				printInt(&Y, N, N);
	//				printf("Z:\n");
	//				printInt(&Z, M, N);
	//				printf("Result:\n");
	//				printInt(&result, M, N);
	//				exit(-1);
	//			}
	//		}
	//	}
	//}
	//printf("TEST PASSED!\tM: %d\tN: %d\t trials: %d\n", M, N, trials);

	
}
