#include <iostream>
#include <string>

#include "hoersaal.h"
#include "technikraum.h"


int main() {
    std::cout << "Hello world" << std::endl;

    hoersaal s1("S0.12ab", 80, true, true, true);
    technikraum t1("S2.99", 0, false, "Abstellraum");


    s1.show_info();
    t1.show_info();
   
}