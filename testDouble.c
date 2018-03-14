#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <math.h>
#include "huanAlgo.h"
#include "cholesky.c"


#define MAXNUM 10
#define MINNUM 1
#define FACTOR 100
#define TENS 1000000 //10^6
#define GEN_INT() ((drand48() * FACTOR) + MINNUM)

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
	double EPS = (double) 1 / (double) TENS;

	double **Z; 
	double **X; 
	double **Y;
	double **result;
	double **multiResult;
	double **A;
	double **B;
	createContiguousArrayDouble(&Z, M, N);
	createContiguousArrayDouble(&X, M, N);
	createContiguousArrayDouble(&Y, N, N);
	createContiguousArrayDouble(&result, M, N);
	createContiguousArrayDouble(&multiResult, M, N);
	createContiguousArrayDouble(&A, M, N);
	createContiguousArrayDouble(&B, M, N);

	//srand(time(NULL));
	srand48((long int) time(NULL));
	for (count = 0; count < trials; count++)
	{
		//Generate randum integers in X;
		//for (i = 0; i < M; i++)
		//{
		//	for(j = 0; j < N; j++)
		//	{
		//		X[i][j] = GEN_INT();
		//		//printf("%6.2f\n", X[i][j]);
		//	}
		//}

		//Generate randum integers in Y;
		for (i = 0; i < N; i++)
		{
			for(j = 0; j < i + 1; j++)
			{
				double value = GEN_INT();
				Y[j][i] = value;
				X[i][j] = value;
			}
		}

		//Multiply out Z
		multiMatrixDouble(Z, X, Y, M, N, N);
		multT(*A, *Y, N, 0); 
		//printMatrix(*A, N);
		//printf("\n\n");
		printMatrix(*Z, N);
		printf("\n\n");
		printMatrix(*Y, N);
		printf("\n\n");
		printMatrix(*X, N);
		//Compute result
		computeMatrixDouble(Z, result, Y, M, N);
		multiMatrixDouble(multiResult, result, Y, M, N, N);


		//printf("EPS: \t%2.20f\n", EPS);
		double maxError = 0.0;
		//Validation
		for (i = 0; i < M; i++)
		{
			for (j = 0; j < N; j++)
			{
				//double temp = (X[i][j] - result[i][j]);
				//double temp2 = fabs(temp);
				//double errorRate = temp2 / X[i][j];
				double temp = (Z[i][j] - multiResult[i][j]);
				double temp2 = fabs(temp);
				double errorRate = temp2 / Z[i][j];
				//if (temp < 0)
				//	printf("Negative.\n");
				//else
				//	printf("Positive.\n");
				//printf("error: \t%2.20f\n", errorRate);
				if (errorRate > EPS)
				{
					printf("ERROR: Result is different\n");
					printf("X:\n");
					printDouble(&X, M, N);
					printf("Y:\n");
					printDouble(&Y, N, N);
					printf("Z:\n");
					printDouble(&Z, M, N);
					printf("Result:\n");
					printDouble(&result, M, N);
					printf("Z[%d][%d] = \t\t%6.20f\n", i, j, Z[i][j]);
					printf("multiResult[%d][%d] = \t%6.20f\n", i, j, multiResult[i][j]);
					exit(-1);
				}
			}
		}
	}
	printf("TEST PASSED!\tM: %d\tN: %d\t trials: %d\n", M, N, trials);

	
}
