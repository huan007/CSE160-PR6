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
	gcc -g -o block testBlockInt.c huanAlgo.o -lm

clean:
	rm *.o
	rm testD
	rm operation
