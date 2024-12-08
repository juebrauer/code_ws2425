#include "hoersaal.h"

using namespace std;


hoersaal::hoersaal(string nr, unsigned int plaetze, bool beamer, bool hat_tafel, bool hat_mikro) :
    raum(nr,plaetze,beamer), tafel(hat_tafel), mikro(hat_mikro)
{
    cout << "Konstruktor der Klasse hoersaal wird aufgerufen!" <<endl;
}

void hoersaal::show_info()
{
    cout << "--------- HÖRSAAL ---------" << endl;
    raum::show_info();
    cout << "Tafel:" << tafel << endl;
    cout << "Mikro:" << mikro << endl;
    cout << "--------- HÖRSAAL ---------" << endl << endl;
};

