#include <stdio.h>
#include <string.h>

int main()
{
    printf("%d\n", strcmp("abc", "abc"));
    printf("%d\n", strcmp("123A", "123a"));
}