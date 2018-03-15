#define ARGS 2
#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))
#define uSECtoSEC 1.0E-6
#define THRESH 1e-13
#define SCALE 100.0
#define TRUE 1
#define FALSE 0

int myRank;
int thread_count;

double get_clock();
void printMatrix(double *A, int N);
int multT(double *result, double *A, int N, int lowerT);
int validate(double *A, double * L, int N, double thresh);
void init_array(int N, int trueRandom, double *A);
void cholesky(double *L, double *A, int N);
