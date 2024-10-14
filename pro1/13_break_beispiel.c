#include <stdio.h>

int main()
{
    int y;
    for (y=1; y<=3; y++)
    {
        for (int x=5; x>0; x--)
        {
            if (x==2)
                break;

            printf("%d ", x);
        }
        printf("\n");        
    }
    printf("y=%d\n", y);
}