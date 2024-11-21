#include <stdio.h>

#define Weeks 2
#define Days 7

int main() {
    float your_weight[Weeks][Days];

    int i = 0;
    for (int w = 0; w < Weeks; w++)
        for (int d = 0; d < Days; d++)
        {
            your_weight[w][d] = i++;
            float* addr = &your_weight[w][d];
            printf("Memory address of your_weight[%d][%d] is : %p\n", w, d, addr);
        } 

    for (int w = 0; w < Weeks; w++)
    {
        for (int d = 0; d < Days; d++)
            printf("%.1f ", your_weight[w][d]);
        printf("\n");
    }

    float* p = your_weight[0];
    for (int i=0; i<Weeks*Days; i++)
    {
        float wert = *(p+i);
        printf("%.1f ", wert);
        if (i % Days == 0)
            printf("\n");
    }  
} // end main