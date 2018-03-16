#include <stdlib.h>
#include <stdio.h>

int main (int argc, char** argv)
{
	int nthread[4];
	int size[7];
	int i, j;
	nthread[0] = 1;
	nthread[1] = 2;
	nthread[2] = 4;
	nthread[3] = 8;

	size[0] = 512;
	size[1] = 1024;
	size[2] = 1536;
	size[3] = 2048;
	size[4] = 3072;
	size[5] = 4096;
	size[6] = 8192;

	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 7; j++)
		{
			printf("%d %d\n", size[j], nthread[i]);
		}
	}
}
