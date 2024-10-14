#include <stdio.h>

int main()
{
    for (int j=1; j<=5; j++)
    {        
        for (int i=1; i<=3; i++)
        {
            if (i == 2)
                continue;

            printf("%d ", i);     
        }
        printf("\n");

        if (j==2)
            continue;
    }
}