#include <stdio.h>
#include <stdlib.h> // malloc & friends

#define MAP_2D_TO_1D_INDEX(dimX,x,y) (y*dimX+x)
typedef unsigned int uint;

int main() {
   uint dimX, dimY;
   printf("Size of Y dimension? ");
   scanf("%d", &dimY);
   printf("Size of X dimension? ");
   scanf("%d", &dimX);

   int* A = malloc(dimY*dimX * sizeof(int));

   int counter = 0;
   for (uint y = 0; y < dimY; y++) {
      for (uint x = 0; x < dimX; x++) {
         uint index = y*dimX + x;
         A[index] = counter++;
      }
   }

   printf("\n");
   for (uint y = 0; y < dimY; y++) {
      for (uint x = 0; x < dimX; x++) {
         printf("%04d ", A[MAP_2D_TO_1D_INDEX(dimX, x, y)]);
      }
      printf("\n");
   }

   free(A);
}