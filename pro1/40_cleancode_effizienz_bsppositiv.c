#include <stdio.h>

#define SIZE 1000

int main() {
    int array[SIZE];
    long long sum_of_squares[SIZE];

    // Initialisiere das Array
    for (int i = 0; i < SIZE; i++) {
        array[i] = i + 1;
    }

    long long nr_multiplies = 0;

    // Berechnung der Summe der Quadrate
    sum_of_squares[0] = array[0] * array[0];
    for (int i = 1; i < SIZE; i++) {
        sum_of_squares[i] = sum_of_squares[i-1] + (long long)array[i] * array[i]; // Keine mehrfachen Array-Zugriffe
        nr_multiplies++;
    }

    for (int i=0; i<10; i++)
        printf("Summe der Quadrate bis zum Array-Element #%d: %lld\n", i, sum_of_squares[i] );

    printf("Ich habe %lld viele Multiplikationen benötigt!\n", nr_multiplies);
    
    return 0;
}

// array[0] = 1 --> sum_of_squares[0] = 1*1 = 1
// array[1] = 2 --> sum_of_squares[1] = 1 + 4 = 5
// array[2] = 3 --> sum_of_squares[2] = 5 + 9 = 14
// array[3] = 4 --> sum_of_squares[3] = 14 + 16 = 30
// usw.


