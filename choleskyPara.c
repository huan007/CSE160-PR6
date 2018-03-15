#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include "cs160validate.h"
#include "cholesky.h"

#ifdef _OPENMP
	#define ARGS_COUNT 3
#else
	#define ARGS_COUNT 2
#endif

int main(int argc, char* argv[]) {

	int n;
	int i,j,k;
	double ts, te; /* Starting time and ending time */
	double start, end;
	double total;
	double time_init, time_calc, time_veri;
	double *A, *L;
	double temp;
	if(argc < ARGS_COUNT) 
	{
		fprintf(stderr,"Wrong # of arguments.\nUsage: %s array_size",argv[0]);
		return -1;
	}
	n = atoi(argv[1]);
#ifdef _OPENMP
	thread_count = atoi(argv[2]);
#else
	thread_count = 1;
#endif
	A = (double *)malloc(n*n*sizeof(double));
	L = (double *)calloc(n*n,sizeof(double));
	printf("Initializing \n");
	start = get_clock();
	init_array(n,0,A);
	end = get_clock();
	total = end - start;
	time_init = total;
	// printf("Initial matrix:\n");
	// printMatrix(A,n);
	printf("Computing the Cholesky Factorization of random %dX%d Matrix\n",n,n);

	/*Serial decomposition*/
	start = get_clock();
	cholesky(L,A,n);
	end = get_clock();
	total = end - start;
	time_calc = total;
	//printf("Decomposed matrix:\n");
	//printMatrix(L,n);
	start = get_clock();
	int badcount = validate(A,L,n,THRESH);
	end = get_clock();
	total = end - start;
	time_veri = total;
	if (badcount == 0)
		printf("solution validates\n");
	else
		printf("solution is invalid, %d elements above threshold\n",badcount);
	cs160validate(A,L,n,THRESH);
	printf("*LOG* \tN: %d", n);
	printf("\tInit:\t %6.4f", time_init);
	printf("\tCalc:\t %6.4f", time_calc);
	printf("\tVeri:\t %6.4f\n", time_veri);
	free(A);
	free(L);
	return badcount;
}
