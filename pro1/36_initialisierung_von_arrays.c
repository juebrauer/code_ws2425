#include <stdio.h>

#define Years 10
#define Weeks 10
#define Days 5

int main() {

   float  your_weight [Years][Weeks][Days];
   double your_weight2[Years][Weeks][Days];
   char   c[10][2][3][4];

   printf("To store the 3D array your_weight[][][] we need %ld Bytes.\n",  sizeof(your_weight)  );
   printf("To store the 3D array your_weight2[][][] we need %ld Bytes.\n", sizeof(your_weight2) );
   printf("To store the 4D array c[][][][] we need %ld Bytes.\n",          sizeof(c)            );

    
} // end main