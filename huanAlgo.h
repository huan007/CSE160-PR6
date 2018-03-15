void createContiguousArrayDouble(double ***u, int localM, int localN);
void createContiguousArrayInt(int ***u, int localM, int localN);
void printInt(signed int ***array, int localM, int localN);
void printDouble(double ***array, double localM, double localN);
void multiMatrixInt(int **A, int **B, int **C, int M, int P, int N);
void multiMatrixDouble(double **A, double **B, double **C, int M, int P, int N);
void sumMatrixInt(int **A, int **B, int M, int N);
void subMatrixInt(int **A, int **B, int M, int N);
void negMatrixInt(int **A, int M, int N);
void computeMatrixDouble(double** Z, double** X, double** Y, int M, int N);
void blockCholeskyDouble(double ***A, double*** L, int blockCount, int blockSize);
void blockInt(int ***A, int*** L, int blockCount, int blockSize);
void blockDouble(double ***A, double*** L, int blockCount, int blockSize);

void computeMatrix(int** Z, int** X, int** Y, int M, int N);
void computeMatrixDouble(double** Z, double** X, double** Y, int M, int N);
void multiMatrixLowerTransInt(int **A, int **B, int **C, int M, int P, int N);
void multiMatrixLowerTransDouble(double **A, double **B, double **C, int M, int P, int N);

void blockInt(int ***A, int*** L, int blockCount, int blockSize);

void printMatrixInt(int *A, int N);
void choleskyInt(int *L, int *A, int N);
int multTInt(int *result, int *A, int N, int lowerT);
void deleteMatrixInt(int **u, int localM, int localN);
void deleteMatrixDouble(double **u, int localM, int localN);
