#include <stdio.h>
#include <stdlib.h> // malloc

int main() {
   unsigned int N;
   int number;

   printf("How many numbers do you want to enter? ");
   scanf("%d", &N);

   int* A = malloc(N * sizeof(int));
   printf("Der Speicherblock für das Array A beginnt an der Adresse: %p\n", A);
   if (A == NULL) {
      printf("Out of memory error!\n");
      exit(1);
   }
      
   /*
   for (unsigned int i = 0; i < N; i++) {
      printf("Enter number #%d: ", i);
      scanf("%d", &number);
      A[i] = number;
   }
   */

   for (unsigned int i = 0; i < N; i++)
      printf("\nnumber #%d: %d", i, A[i]);

   free(A);
   
}