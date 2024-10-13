#include <stdio.h>
#include <stdlib.h> // für rand()
#include <time.h>   // für time()

int main()
{    
    char wahl;
    do
    {
        
        int zufallszahl = rand() % 6 + 1;
        printf("Der Würfel zeigt eine %d\n", zufallszahl);

        printf("\nWillst du weitermachen (j=ja,n=nein) ?");
        scanf("%c", &wahl);

        // Lösche alle weiteren Zeichen aus dem Tastaturpuffer jetzt heraus
        while (getchar() != '\n')
        {
            
        }

    } while (wahl == 'j' || wahl == 'J');
    printf("Programmende!\n");
}