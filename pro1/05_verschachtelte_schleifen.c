#include <stdio.h>

int main()
{  
  for (int a=1; a<=3; a++)
  {  
    printf("-----\n"); // CMD1
    for (int b=1; b<=5; b++) // CMD2
    {
        printf("a=%d b=%d\n", a,b);
    }
    printf("+++++\n"); // CMD3
  }

  printf("Ende des Programms erreicht!\n");
}