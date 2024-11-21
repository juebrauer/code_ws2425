#include <stdio.h>

float average(float numbers[], int how_many) {
   float sum = 0.0f;
   for (int j = 0; j < how_many; j++)
      sum += numbers[j];
   return sum/how_many;
}

float average2(float numbers[]) {
   float sum = 0.0f;
   int i = 0;
   while (numbers[i] != -1)
   {
      sum += numbers[i++];    
   }
   printf("sum=%f\n", sum);
   printf("i=%d\n",i);
   return sum/i;
}

float average3(double* numbers) {
   double sum = 0.0f;
   int i = 0;
   while (*(numbers+i) != -1)
   {
      printf("numbers[%d] liegt an Speicheradresse %p\n", i, &(numbers[i]));
      sum += numbers[i++];    
   }
   printf("sum=%f\n", sum);
   printf("i=%d\n",i);
   return sum/i;
}

int main() {

    int v = 42;
    int* pv = &v;

    double numbers[101];
        
    printf("\nPlease enter up to 100 numbers. Enter -1 to stop\n");   
    int i = 0;
    do {
        printf("Enter number #%d : ", i+1);
        double f;
        scanf("%lf", &f);
        if (f==-1.0)
        {           
            break;
        }   
        numbers[i] = f;
        i++;
    } while (i<=99);

    // Markiere das Ende im Array
    numbers[i] = -1;

    if (i>0)
        printf("\nAverage of the %d numbers you entered is : %.2f\n",
                i, average3(numbers) );

} // end main