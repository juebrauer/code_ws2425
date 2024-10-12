#include <stdio.h> // für printf()
#include <stdlib.h> // für rand()
#include <time.h>   // für time()

int main()
{
    printf("RAND_MAX=%d\n", RAND_MAX);

    // Initialisiere den Zufallsgenerator mit der aktuellen Zeit
    srand(time(NULL));

    // Erzeuge eine Zufallszahl zwischen 0 und RAND_MAX
    for (int i=1; i<=20; i++)
    {        
        printf("%d ", rand() % 6 + 1);
    }
    printf("\n");
}