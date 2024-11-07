#include <stdio.h>
#define pi 3.14159f
float circumference = -999.0f;

void ShowProgramInfo() {
   printf("This program can compute the circumference and the area of a circle\n");
   printf("given just the radius of the circle.\n\n");
}

float circle_circumference(float r) {
   circumference = 2.0f * pi * r;
   return circumference;
}

float circle_area(float r) {
   float area = pi * r * r;
   return area;
}

int main() {
   ShowProgramInfo();     
   printf("\ncircumference before calling all functions = %.1f", circumference);
   float radius;
   printf("\nEnter the radius of your circle: ");
   scanf("%f", &radius);
   printf("\nA circle with radius %.2f cm has\n", radius);
   printf("\ta circumference of %.2f cm and\n", circle_circumference(radius));
   printf("\tan area of %.2f cm^2\n", circle_area(radius));
   printf("\ncircumference after calling all functions = %.1f\n", circumference);
}