#include <stdio.h>

int main() {
    int note = 2;

    switch (note*10/(5*2)) {
        case 2: printf("Das ist noch gut!\n"); break;
        case 3: printf("Das ist nicht mehr so gut!\n"); break;
        case 4: printf("Das ist gerade noch ausreichend!\n"); break;
    }

    return 0;
}
