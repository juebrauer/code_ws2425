#include <stdio.h>

int main()
{
   long int  x = 123;
   void* y = &x;
   long int  z = *((long int*)y);
   void* u = (y+1);
   long int* v = (y+1000);

   printf("Speicheradresse y=%p\n", y);
   printf("Speicheradresse u=%p\n", u);
   printf("Speicheradresse --u=u-1=%p\n", u-1);
   
   printf("%ld\n", x);
   printf("%ld\n", z);
   printf("%ld\n", *(&x));
   printf("%ld\n", *((long int*)--u));
   printf("%ld\n", *v);

}