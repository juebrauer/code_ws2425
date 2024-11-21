#include <stdio.h>

int main()
{
   short int v = 42;
   printf("Anzahl der Bytes, um v zu speichern: %ld\n", sizeof(v));

   
   unsigned long pv;

   pv = (unsigned long)&v;

   printf("Variable v is stored at "
          "memory location %p\n", (void*)pv);

   printf("Anzahl der Bytes, um den Pointer zu speichern: %ld\n", sizeof(pv));

   printf("Wert von v: %d\n", v);
   printf("Wert von v nochmal: %d\n", *((short int*)pv));
   
}