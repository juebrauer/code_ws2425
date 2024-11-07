#include <stdio.h>
#include <math.h>

int main()
{
    double ergebnis = 0.0;

    for (unsigned int i=1; i<=1000000000; i++)
    {
        double wert = sin(i);
        ergebnis += wert;
    }

    printf("Das ergebnis ist : %lf\n", ergebnis);
}