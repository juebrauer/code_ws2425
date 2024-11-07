#include <stdio.h>

void c()
{
   printf("We are now in function c()\n");
}

void b()
{
   printf("We are now in function b()\n");
   c();
   printf("Willkommen zurück von dem Aufruf von c()!\n");
}

void a()
{
   printf("We are now in function a()\n");
   b();
   printf("Willkommen zurück von dem Aufruf von b()!\n");
}

int main()
{
   a();
   printf("Willkommen zurück von dem Aufruf von a()!\n");
}