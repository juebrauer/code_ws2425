#include <stdio.h>
#include <limits.h> // for value ranges of integers
#include <float.h>  // for value ranges of floats

int main()
{
    // 16 Bits
    // 2*2*2*...*2 = 2^16   0100011000100100
    //unsigned short a = 0-2;
    //printf("a=%d\n", a);



   printf("1. Number of bytes needed to represent each data type:\n");
   printf("_Bool              : %ld Byte(s)\n", sizeof(_Bool)); //_Bool is data type in C since C99 standard
   printf("char               : %ld Byte(s)\n", sizeof(char));
   printf("uchar              : %ld Byte(s)\n", sizeof(unsigned char));
   printf("short int          : %ld Byte(s)\n", sizeof(short int));
   printf("unsigned short int : %ld Byte(s)\n", sizeof(unsigned short int));
   printf("int                : %ld Byte(s)\n", sizeof(int));
   printf("unsigned int       : %ld Byte(s)\n", sizeof(unsigned int));
   printf("long long          : %ld Byte(s)\n", sizeof(long long));
   printf("unsigned long long : %ld Byte(s)\n", sizeof(unsigned long long));
   printf("float              : %ld Byte(s)\n", sizeof(float));
   printf("double             : %ld Byte(s)\n\n", sizeof(double));

   printf("2. Value ranges per data type:\n");
   printf("CHAR_MIN   = %i\n", CHAR_MIN);    // MIN char
   printf("CHAR_MAX   = %i\n", CHAR_MAX);    // MAX char
   //printf("UCHAR_MIN  = %i\n", UCHAR_MIN);    // MIN unsigned char (is not defined!)
   printf("UCHAR_MAX  = %i\n", UCHAR_MAX);   // MAX unsigned char
   printf("SHRT_MIN   = %i\n", SHRT_MIN);    // MIN short int
   printf("SHRT_MAX   = %i\n", SHRT_MAX);    // MAX short int
   printf("USHRT_MAX  = %i\n", USHRT_MAX);   // MAX unsigned short int
   printf("INT_MIN    = %i\n", INT_MIN);     // MIN int
   printf("INT_MAX    = %i\n", INT_MAX);     // MAX int
   printf("UINT_MAX   = %u\n", UINT_MAX);    // MAX unsigned int
   printf("LLONG_MIN  = %lli\n", LLONG_MIN);   // MIN long long
   printf("LLONG_MAX  = %lli\n", LLONG_MAX);   // MAX long long
   printf("ULLONG_MAX = %llu\n", ULLONG_MAX);  // MAX unsigned long long
   printf("FLT_MIN    = %e\n", FLT_MIN);     // Smallest (not most negative!) float number inequal to 0
   printf("FLT_MAX    = %e\n", FLT_MAX);     // MAX float
   printf("DBL_MIN    = %e\n", DBL_MIN);     // Smallest (not most negative!) double number inequal to 0
   printf("DBL_MAX    = %e\n", DBL_MAX);     // MAX double

}