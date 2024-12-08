#include "technikraum.h"


technikraum::technikraum(std::string nr, unsigned int plaetze, bool beamer, std::string wozu) :
    raum(nr,plaetze,beamer), nutzen(wozu)
{
    std::cout << "Konstruktor der Klasse technikraum wird aufgerufen!" << std::endl;
}

void technikraum::show_info()
{
    std::cout << "--------- TECHNIKRAUM ---------" << std::endl; 
    raum::show_info();
    std::cout << "Wozu verwendet? : " << nutzen << std::endl;
    std::cout << "--------- TECHNIKRAUM ---------" << std::endl << std::endl;
}
