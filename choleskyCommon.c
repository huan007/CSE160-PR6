#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include "cs160validate.h"
#include "choleskyCommon.h"

#define MAXNUM 9
#define MINNUM 1e-2

#ifdef _OPENMP
#include <omp.h>
#endif

// Macro to define index into a linear array for 2D indexing. Stored 
// row by row.
#define IDX(i,j,n) ((i*n)+j)

/* return a clock value with usec precision */
double get_clock() {
    struct timeval tv;
    int status;
    status = gettimeofday(&tv, (void *) 0);
    if(status<0)
        printf("gettimeofday error");
    return (tv.tv_sec * 1.0 + tv.tv_usec * 1.0E-6);
}

void printMatrix(double *A, int N)
{
	int i,j;
	for(i = 0; i < N; i++){
		for(j = 0; j < N; j++)
			printf("%lf ", A[IDX(i,j,N)]);
		printf("\n");
	}
}
/* Multiply A*A^T.  
 * double *result - result matrix
 * double * A - source matrix
 * int N - size of matrix (N x N);
 * int lowerT - A is lower triangular
 */
int multT(double *result, double *A, int N, int lowerT)
{
	int i,j,k;
	bzero(result, N*N*sizeof(double));
	printf("Thread count: %d\n", thread_count);
	int chunk = ceil(N/(thread_count*32));
	if (chunk == 0)
		chunk = 1;
#pragma omp parallel for num_threads(thread_count) schedule (dynamic, chunk) \
	private (i,j,k)
	for(i = 0; i < N; i++)
	{
		#ifdef _OPENMP
		//printf("Hello from thread %d\n", omp_get_thread_num());
		#endif
		/* Result is symmetric, just compute upper triangle */
		for(j = i; j < N; j++) 
		{
#pragma omp private (sum)
			double sum = 0.0;
			//printf("Start sum [%d][%d]\n", i, j);
			/* if A is lower Triangular don't multiply zeroes */
			for(k = 0; k < (!lowerT ? N : j+1) ; k++)
			{
				//printf("%3.6f\t %3.6f\n", A[IDX(i,k,N)], A[IDX(j,k,N)]);
				sum += A[IDX(i,k,N)] * A[IDX(j,k,N)];
			}
#pragma omp critical
			{
			result[IDX(i,j,N)] = sum;
			result[IDX(j,i,N)] = sum; /*enforce symmetry */
			}
		}
		//printf("Outside\n");
	}
	//printMatrix(result, N);
	return 0;
}
	
/* Validate that A ~= L*L^T 
 * double * A -  NxN symmetric positive definite matrix
 * double * L -  NxN lower triangular matrix such that L*L^T ~= A
 * int N      -  size of matrices
 * thresh     -  threshold considered to be zero (1e-14 good number)
 *
 * Returns # of elements where the residual abs(A(i,j) - LL^T(i,j)) > thresh
*/
int validate(double *A, double * L, int N, double thresh)
{
	double *R = malloc(N*N * sizeof(double));
	multT(R,L,N,TRUE);
	int badcount = 0;
	int i,j;
	double rdiff; /* relative difference */
	int chunk = ceil(N/(thread_count*32));
	if (chunk == 0)
		chunk = 1;
#pragma omp parallel for num_threads(thread_count) schedule (static, chunk) \
	private (i,j,rdiff) shared(badcount)
	for (i = 0 ; i < N; i++)
	{
		for(j = 0; j < N; j ++)
		{
			if (A[IDX(i,j,N)] == 0)
				printf("Validate: ZERO\n");
			if (isnan(-A[IDX(i,j,N)]))
				printf("Validate: NaN!\n");
			rdiff = fabs((R[IDX(i,j,N)] - A[IDX(i,j,N)])/A[IDX(i,j,N)]);
			//printf("R[%d][%d]: %3.20f\n", i,j,R[IDX(i,j,N)]);
			//printf("A[%d][%d]: %3.20f\n", i,j,A[IDX(i,j,N)]);
			//printf("rdiff :%3.20f\n", rdiff);
			//printf("thresh :%3.20f\n", thresh);
			if (rdiff > thresh)
#pragma omp critical
			{
				printf("(%d,%d):R(i,j):%5.16f,A(i,j):%5.16f (delta: %5.16e)\n",
					i,j,R[IDX(i,j,N)],A[IDX(i,j,N)],
					rdiff);
				printf("R[%d][%d]: %3.20f\n", i,j,R[IDX(i,j,N)]);
				printf("A[%d][%d]: %3.20f\n", i,j,A[IDX(i,j,N)]);
				printf("rdiff :%3.20f\n", rdiff);
				printf("thresh :%3.20f\n", thresh);

				badcount++; 
			}
		}
	}
	free(R);
	return badcount;
}
/* Initialize the N X N  array with Random numbers
 * In such a way that the resulting matrix in Symmetric
 * Positive definite (hence Cholesky factorization is valid)
 * args:
 * 	int N - size of the array
 * 	int trueRandom  - nonzero, seed with time of day, 0 don't seed
 *	double **A - N x N double array, allocated by caller
*/
void init_array(int N, int trueRandom, double *A) {
	int i,j,k;
	double start, end, total;
	struct drand48_data rbuf;
	if (trueRandom)
		srand48_r((long int) time(NULL),&rbuf);
	else
		srand48_r(1L,&rbuf);

	double *B = calloc(N * N, sizeof(double));

	printf("Random number generation\n");
	start = get_clock();
	for(i = 0; i < N; i++)
	{
		double *localBuf = malloc(N * sizeof(double));
		for(j = 0; j < N; j++) 
		{
			drand48_r(&rbuf, &(localBuf[j]));
			if (localBuf[j] == 0)
				printf("ZERO\n");
			localBuf[j] *= SCALE;
			//printf("number: %5.12f\n", number);
			//drand48_r(&rbuf,&B[IDX(i,j,N)]);
			//printf("B(%d)(%d): %5.12f\n", i, j, B[IDX(i,j,N)]);
			//if (B[IDX(i,j,N)] == 0)
			//	printf(" B(%d)(%d) ZERO\n", i, j);
		}
		memcpy(&(B[IDX(i,0,N)]), localBuf, N * sizeof(double));
		free(localBuf);
	}
	printf("done random number generation\n");
	end = get_clock();
	total = end - start;
	printf("Time taken to generate randoms: %5.4f\n", total);
	//printMatrix(B,N);

	/* Compute B*B^T to get symmetric, positive definite */
	start = get_clock();
	multT(A,B,N,0);
	end = get_clock();
	total = end - start;
	printf("Time taken to multiply matrix: %5.4f\n", total);
	free (B);
}

/* Compute the Cholesky Decomposition of A 
 * L - NxN result matrix, Lower Triangular L*L^T = A
 * A - NxN symmetric, positive definite matrix A
 * N - size of matrices;
 */
void cholesky(double *L, double *A, int N)
{
	int i,j,k;
	bzero(L,N*N*sizeof(double));
	double temp;
	int chunk = ceil(N/(thread_count*32));
	if (chunk == 0)
		chunk = 1;
#pragma omp parallel for num_threads(thread_count) schedule (dynamic, chunk) \
	private(i,j,k,temp)
	for (i = 0; i < N; i++){
		for (j = 0; j < (i+1); j++) {
			temp = 0;
			/* Inner product of ith row of L, jth row of L */
			for (k = 0; k < j; k++)
				temp += L[IDX(i,k,N)] * L[IDX(j,k,N)];
#pragma omp critical
			{
			if (i == j)
				L[IDX(i,j,N)] = sqrt(A[IDX(i,i,N)] - temp);
			else {
				L[IDX(i,j,N)] = (A[IDX(i,j,N)] - temp)/ L[IDX(j,j,N)];
			}
			}
		  }
	}

}

/* Compute the Cholesky Decomposition of A 
 * L - NxN result matrix, Lower Triangular L*L^T = A
 * A - NxN symmetric, positive definite matrix A
 * N - size of matrices;
 */
void choleskySingle(double *L, double *A, int N)
{
	int i,j,k;
	bzero(L,N*N*sizeof(double));
	double temp;
	int chunk = ceil(N/(thread_count*32));
	if (chunk == 0)
		chunk = 1;
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
