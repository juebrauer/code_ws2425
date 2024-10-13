#include <stdio.h>

int main()
{
    printf("while-Schleife:\n");
    int i;
    i=1;
    while (i<=10)
    {
        printf("%d ", i);
        i++;
    }
    printf("\n");

    printf("\ndo-while-Schleife:\n");
    i=1;
    do
    {
        printf("%d ", i);
        i++;
    } while (i<=10);
}