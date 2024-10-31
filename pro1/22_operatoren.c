#include <stdio.h>
#include <stdlib.h>

int main()
{
  //                       16 8 4 2 1
  int b = 8; // 8(10) = 8(2): 00...0      0 1 0 0 0
             // 7(10) = 7(2): 00...0      0 0 1 1 1
             // -----------------------------------
             // 15(10)=15(2): 00...0      0 1 1 1 1
  int a = b | 7;
  printf("a=%d\n", a);

  int c = 3; // 3(10) = 3(2): 00...0      0 0 0 1 1
             // 3 << 2      : 00...0      0 1 1 0 0
  int d = c << 2;
  printf("d=%d\n", d);

  int e = -5;
  int f = -e;
  for (int i=1; i<=5; i++)
  {
    f = -f;
    printf("f=%d\n", f);
  }

  int wert1 = +123;
  int wert2 = 546;
  //if ((wert1<0) && (wert2>0))
  //  wert2 *= -1;
  //if ((wert1>0) && (wert2<0))
  //  wert2 *= -1;
  int sign = wert1/abs(wert1);
  printf("Das Vorzeichen von wert1 ist %d\n", sign);
}