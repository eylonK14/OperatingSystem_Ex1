#include "poisson.h"

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