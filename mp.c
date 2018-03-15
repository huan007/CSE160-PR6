#include <stdlib.h>
#include <stdio.h>

#ifdef _OPENMP
#include <omp.h>
#endif

int main(int argc, char **argv)
{
	int total = atoi (argv[1]);
	int nprocs = atoi(argv[2]);
	int rank = 0;


	int i,j,k;
	struct drand48_data rbuf;
	srand48_r(1L, &rbuf);

	printf("nprocs: %d\n", nprocs);
	#pragma omp parallel for num_threads(nprocs) schedule (static, 1)
	for (i = 0; i < total; i++)
	{
#ifdef _OPENMP
	rank = omp_get_thread_num();
#endif
		for (j = 0; j < total; j++)
		{
			double number;
			drand48_r(&rbuf, &number);
			if (number == 0)
				printf("ZERO\n");
			number *= 100;
			//printf("(%d) Number %d: %5.12f\n", rank, i, number);
		}
	}
}
