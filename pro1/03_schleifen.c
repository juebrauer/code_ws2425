#include <stdio.h>

int main()
{
  double kapital = 1000;
  double zinssatz = 3.6;
  int dauer = 8;  
  
  int jahr;
  for (jahr=1; jahr<=dauer; jahr++)
  {
      kapital = kapital + (zinssatz/100)*kapital;
      printf("Nach Jahr %d: %.2f\n", jahr, kapital);
  } 
  printf("\nOk, nach %d Jahren hast du ein Kapital in Höhe von %.0f\n",
          jahr-1, kapital);
}
