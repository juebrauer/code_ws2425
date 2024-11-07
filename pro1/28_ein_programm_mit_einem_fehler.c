#include <stdio.h>

int main()
{
    int umsaetze[7] = {10,20,9,25,50,60,15};

    int summe;
    for (int i=0; i<7; i++)
    {
        summe += umsaetze[i];
    }

    printf("Summe der Umsätze in dieser Woche: %d\n", summe);
}