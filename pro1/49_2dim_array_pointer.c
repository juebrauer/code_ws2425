#include <stdio.h>
#include <stdlib.h> // malloc & friends
typedef unsigned int uint;

int main() {
   uint dimX, dimY;
   printf("Size of y dimension? ");
   scanf("%d", &dimY);
   printf("Size of x dimension? ");
   scanf("%d", &dimX);

   int** myArray2D = malloc(dimY * sizeof(int*));
   for (uint y = 0; y < dimY; y++)
      myArray2D[y] = malloc(dimX * sizeof(int));

   int counter = 0;
   for (uint y = 0; y < dimY; y++)
      for (uint x = 0; x < dimX; x++)
         myArray2D[y][x] = counter++;

   for (uint y = 0; y < dimY; y++) {
       for (uint x = 0; x < dimX; x++)
            printf("%04d ", myArray2D[y][x]);
        printf("\n");
   }

   for (uint y = 0; y < dimY; y++)
      free (myArray2D[y]);
   
   free(myArray2D);
}