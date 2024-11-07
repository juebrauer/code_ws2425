#include <stdio.h>

float radius;

#define pi 3.14159f

void ShowProgramInfo() {
   printf("This program can compute the\n");
   printf("circumference and the area of a circle\n");
   printf("given just the radius of the circle.\n\n");
}

float circle_circumference(float r) {
   float circumference = 2.0f * pi * r;
   printf("radius=%f\n", radius);
   return circumference;
}

float circle_area(float r) {
   float area = pi * r * r;
   printf("radius=%f\n", radius);
   return area;
}

void main(void) {
   ShowProgramInfo();

   printf("Enter the radius of your circle: ");
   scanf("%f", &radius);

   printf("\nA circle with radius %.2f cm has\n", radius);
   printf("\ta circumference of %.2f cm and\n", circle_circumference(radius));
   printf("\tan area of %.2f cm^2\n", circle_area(radius));
   
}

