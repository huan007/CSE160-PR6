algo: huanAlgo.c
	gcc -g -c huanAlgo.c -lm


test: algo testInt.c
	gcc -g -o test testInt.c huanAlgo.o

testd: algo testDouble.c
	gcc -g -o testd testDouble.c huanAlgo.o -lm

