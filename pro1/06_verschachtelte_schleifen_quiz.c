#include <stdio.h>

int main()
{  
  for (int a=1; a<=10; a++)
  {  
    for (int b=1; b<=a; b++) // CMD1
    {
        printf("*");
    }
    printf("\n"); // CMD2
  }

  printf("Ende des Programms erreicht!\n");
}