#include <stdio.h>
#include <time.h>

int main()
{
    clock_t start = clock();

    int N = 100000000;
    double result = 0.0;
    for (int i=-N/2; i<=N/2; i++)
    {
        if (i<0)
            result += 0.1;
        else
        if (i>0)
            result += 0.5;
        else
        if (i==0)
            result += 0.9;
    
        result += 0.001;
    }

    clock_t end = clock();

    double time_spent;
    time_spent = (double)(end-start) / CLOCKS_PER_SEC;

    printf("result=%f\n", result);
    printf("Duration: %f\n", time_spent);
   
}