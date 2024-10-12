#include <stdio.h> // für printf()

int main()
{
    int zahl;

    do {
        printf("Bitte gib eine positive Zahl ein: ");
        scanf("%d", &zahl);
    } while (zahl <= 0);

    printf("Danke! Du hast eine positive Zahl eingegeben: %d\n", zahl);
}