#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_NUMBERS 1000
#define MAX_LEN_INVALID_TOKEN 100

int calculate_sum(int numbers[], int N)
{
    int sum = 0;
    for (int i=0; i<N; i++)
    {
        sum += numbers[i];
    }
    return sum;
}

float calculate_average(int numbers[], int N)
{
    float average = calculate_sum(numbers, N) / (float)N;
    return average;
}

void bubble_sort(int numbers[], int N)
{
    bool swapped;
    do
    {
        swapped = false;
        for (int i=0; i<N-1; i++)
        {
            if (numbers[i] > numbers[i+1])
            {
                // Zahlen sind in falscher Reihenfolge! Daher: beide Zahlen vertauschen
                // i:            0      1      2      3      4
                // numbers:    100    95     87    120     203
                // numbers:     12    20     30     44      99
                int tmp = numbers[i];
                numbers[i] = numbers[i+1];
                numbers[i+1] = tmp;
                swapped = true;
            }
        }
    } while (swapped);
}

float calculate_median(int numbers[], int N)
{
    bubble_sort(numbers, N);

    bool array_size_even = (N%2==0);

    if (array_size_even)
    {
        // i:            0      1      2      3      4      5
        // numbers:     12     44     46     51     59     64
        int lower_median = numbers[N/2-1];
        int upper_median = numbers[N/2];
        float median = (lower_median+upper_median)/2.0;
        return median;
    }
    else
    {
        return numbers[N/2];
    }
}


int main() {
    FILE *file;
    int numbers[MAX_NUMBERS]; // Array, in dem wir alle Zahlen speichern
    int number;
    int numbers_read = 0;    

    // Datei öffnen
    file = fopen("zahlen.txt", "r");
    if (file == NULL) {
        printf("Fehler beim Öffnen der Datei.\n");
        return 1;
    }

    // Zahlen einlesen und zur Summe hinzufügen
    int rv;
    do {
        rv = fscanf(file, "%d", &number);
        if (rv == 1) {
            // Gültige Zahl wurde eingelesen
            numbers[numbers_read] = number;
            numbers_read++;
        } else if (rv == 0) {
            // Ungültige Eingabe überspringen            
            char txt[MAX_LEN_INVALID_TOKEN];
            fscanf(file, "%s", txt); // Überspringt das ungültige Token
            printf("Unültige Eingabe gefunden: %s\n", txt);
        }
    } while (rv != EOF);

    // Datei schließen
    fclose(file);

    printf("Eingelesene Zahlen:\n");
    for (int i=0; i<numbers_read; i++)
    {
        printf("%d ", numbers[i]);
    }
    printf("\n--------------\n");
    printf("Summe = %d\n", calculate_sum(numbers, numbers_read));
    printf("Durchschnitt = %f\n", calculate_average(numbers, numbers_read));
    printf("Median = %f\n", calculate_median(numbers, numbers_read));
    
    printf("Sortierte Zahlen:\n");
    for (int i=0; i<numbers_read; i++)
    {
        printf("%d ", numbers[i]);
    }
    printf("\n");

    return 0;
}
