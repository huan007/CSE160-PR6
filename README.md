CSE 160 PR6 - Block Cholesky Factorization
=========

Description
-----
Parallel & Block Cholesky Factorization 

Install & Requirements
-----
In order to compile this project, you need to install pthread.
To Install pthread in Ubuntu run the following command:
```
sudo apt-get install libpthread-stubs0-dev libomp-dev
```
Then run Make to compile the file.
```
make cholesky
make blockCholesky
make blockCholeskyMP
```

How to run the program
-----
The program's argument format goes as follow:
```
cholesky <matrix_size>
blockCholesky <blockSize> <blockCount> <numTrials>
blockCholeskyMP <blockSize> <blockCount> <numTrials> <nthread>
```

where ```<matrix_size> = <blockSize> * <blockCount>```
