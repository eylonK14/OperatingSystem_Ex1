#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int improvement(int *arr, int size)
{
	int best = 0;
	for(int a = 0; a < size; a++)
	{
		int sum = 0;
		for(int b = a; b < size; b++)
		{
			sum += arr[b];
			best = max(best, sum);
		}
	}
	return best;
}

int main(int argc, char *argv[])
{
	if (argc != 2) {
		printf("Usage: %s <seed> <array_size>\n", argv[0]);
		return 1;
	}
	int seed = atoi(argv[1]);
	int size = atoi(argv[2]);
	int *arr = (int *)malloc(size * sizeof(int));
	srand(seed);
	for(int i = 0; i < size; i++) {
		arr[i] = rand() % 100 - 25;
	}
	int best = improvement(arr, size);
	printf("Best sum: %d\n", best);
	return 0;
}