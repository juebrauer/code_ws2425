#include <stdio.h>

void a(int val); // that's the forward declaration of function a(). It is also called “function prototype”

void b(int val) {
   printf("We are now in^ function b(), val=%d\n", val);
   if (val == 2)
      a(val + 1); // a() can be called from here due to the forward declaration of a()
   printf("We are still in function b(), val=%d\n", val);
}

void a(int val) // a() is implemented here
{
   printf("We are now in function a(), val=%d\n", val);
   if (val == 2)
      b(val); // b() can be called from here
   printf("We are still in function a(), val=%d\n", val);
}

main()
{
   a(2);
}