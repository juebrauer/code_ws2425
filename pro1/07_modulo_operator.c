#include <stdio.h>

int main()
{
    int a = 11;
    int b = 4;
    int c = a/b; // Integer-Division = ganzzählige Division
    printf("%d/%d = %d\n", a,b,c);
    //int rest = a % b; // das Ergebnis wird immer eine Zahl sein zwischen 0 bis (b-1)

    // 11/4=2
    // 11%4=3
    int rest = a-(a/b)*b;
    printf("Rest: %d\n", rest);

    float d = 10;
    float e = 3;
    float f = d/e; // Floating-Point-Division = Division mit gebrochenen Zahlen
    printf("%f/%f = %f\n", d,e,f);

    for (int i=1; i<=100; i++)
    {
        if (i%5==0)
            printf("%d ", i);
    }
    printf("\n");
}