algo: huanAlgo.c
	gcc -g -c huanAlgo.c -lm


test: algo testInt.c
	gcc -g -o test testInt.c huanAlgo.o -lm

test2: algo testInt2.c
	gcc -g -o test2 testInt2.c huanAlgo.o -lm

testd: algo testDouble.c
	gcc -g -o testd testDouble.c huanAlgo.o -lm

operation: algo testOperationInt.c
	gcc -g -o operation testOperationInt.c huanAlgo.o -lm

block: algo testBlockInt.c
	gcc -g -o block testBlockInt.c huanAlgo.o cholesky.c -lm

blockd: algo testBlockDouble.c
	gcc -g -o blockd testBlockDouble.c huanAlgo.c cholesky.c -lm -lpthread -fopenmp

chopara: cholesky.c cholesky.h choleskyPara.c
	gcc -g -o chopara -O3 choleskyPara.c cholesky.c cs160validate.c -lm -fopenmp -lpthread

choser: cholesky.c cholesky.h choleskyPara.c
	gcc -g -o choser -O3 choleskyPara.c cholesky.c cs160validate.c -lm 

cho: algo chopara choser cholesky.c cholesky.h choleskyPara.c
	gcc -g -o chopara -O3 choleskyPara.c cholesky.c cs160validate.c -lm -fopenmp -lpthread
	gcc -g -o choser -O3 choleskyPara.c cholesky.c cs160validate.c -lm 

mp:	mp.c
	gcc -g -o mp mp.c -lm -lpthread -fopenmp
	gcc -g -o mpser mp.c -lm -lpthread 

clean:
	rm *.o
	rm testD
	rm operation
	rm block
	rm blockd
	touch cholesky.c 
	touch choleskyPara.c
