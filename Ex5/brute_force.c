#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int brute_force(int *arr, int size)
{
	int best = 0;
	for(int i = 0; i < size; i++)
	{
		for(int j = i; j < size; j++)
		{
			int sum = 0;
			for(int k = i; k <= j; k++)
			{
				sum += arr[k];
			}
			best = best > sum ? best : sum;
		}
	}
	return best;
}

int main(int argc, char *argv[])
{
	if (argc != 3) {
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
	int best = brute_force(arr, size);
	printf("Best sum: %d\n", best);
	return 0;
}