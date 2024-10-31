#include <stdio.h>

int main()
{
    double a = 1.0;

    for (int i=1; i<=324; i++)
    {
        a = a / 10.0;
        printf("%03d: a=%.350f\n", i, a);
    }
}