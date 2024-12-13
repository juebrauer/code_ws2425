#include <stdio.h>
#include <stdlib.h> // malloc & friends

int main() {
    unsigned int array_size = 3;
    int* A = malloc(array_size * sizeof(int));
    if (A == NULL) {
        printf("Out of memory error!\n");
        exit(1);
    }
    printf("I have pre-allocated memory for %d numbers.\n\n", array_size);

    int numbers_stored = 0;
    while (1) {
        printf("Enter new number: ");
        int n;
        scanf("%d", &n);
        numbers_stored++;

        if (numbers_stored > array_size) {
            printf("Ich reserviere neuen Speicher!\n");
            printf("\talte Speicheradresse für Array A: %p\n", A);
            A = realloc(A, numbers_stored * sizeof(int));
            printf("\tneue Speicheradresse für Array A: %p\n", A);
            if (A != NULL) {
                array_size = numbers_stored;
                printf("Array has been resized to size %d.\n", array_size);
            } else {
                printf("Out of memory error!\n");
                exit(1);
            }
        }
        A[numbers_stored - 1] = n;
    } // end while
    free(A);
}