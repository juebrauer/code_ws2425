#include <stdio.h>

int main()
{
    // (2<-3) ? printf("Hallo!") : printf("Tschuess!");

    int a;
    int b;
    a = 15;
    b = 12;
    int maximum;
    maximum = (a>b) ? a : b;
    printf("maximum=%d\n", maximum);
}