#include <stdio.h>
#include <stdlib.h> // malloc


int main() {
    char* A = NULL; 
    while (1) {
        printf("\nHow much MB do you want? ");
        unsigned long long mb;
        scanf("%lld", &mb);

        if (mb == 0)
            break;

        if (A != NULL)
        {
            printf("Gebe den Speicherblock beginnend ab %p wieder frei!\n", A);
            free(A);
        }

        unsigned long long  number_of_bytes_to_reserve = mb * 1024 * 1024;
        printf("Ok, du willst also %lld !\n", number_of_bytes_to_reserve);
        A = malloc(number_of_bytes_to_reserve);

        if (A == NULL) {
            printf("Out of memory!\n");
            exit(1);
        }
        else {
            printf("\tReserved %lld MB of memory.\n", mb);
            printf("\tMemory starts at address %p\n", A);

            for (unsigned long long byte_nr=0; byte_nr<number_of_bytes_to_reserve; byte_nr++)
            {
                A[byte_nr] = 42;
            }
        }


    } // end while


}