#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define AMOUNT_OF_PARAMETERS 3

long double factorial(double n)
{
    // iterative method
    long double result = 1;
    for(int i = 1; i <= n; i++)
    {
        result *= i;
    }
    return result;
}

long double px(double lambda, double k)
{
    return (powl(lambda, k) / factorial(k)) * expl(-lambda);
}

int main(int argc, char* argv[])
{
    if(argc != AMOUNT_OF_PARAMETERS)
    {
        printf("Error\n");
        return 1;
    }

    int lambda = atoi(argv[1]);
    int k = atoi(argv[AMOUNT_OF_PARAMETERS - 1]);


    printf("%Lf\n", px(lambda, k));
    return 0;
}