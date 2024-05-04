#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int kadanes_alg(int *arr, int size)
{
	int max_sum = 0;
	int current_sum = 0;
	for(int i = 0; i < size; i++)
	{
		current_sum = arr[i] > current_sum + arr[i] ? arr[i] : current_sum + arr[i];
		max_sum = max_sum > current_sum ? max_sum : current_sum;
	}
	return max_sum;
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
	int best = kadanes_alg(arr, size);
	printf("Best sum: %d\n", best);
	return 0;
}