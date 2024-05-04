#include "poisson.h"

#define VALUES 5

int main(int argc, char *argv[])
{

    int kValues[] = {1, 10, 2, 3, 3};
    int lambdaValues[] = {2, 2, 2, 3, 100};

    for (int i = 0; i < VALUES; i++)
    {
        printf("Run #%d: lambda = %d, k = %d, poisson = %Lf\n", (i + 1), 
        lambdaValues[i], kValues[i], px(lambdaValues[i], kValues[i]));
    }
    
    return 0;
}