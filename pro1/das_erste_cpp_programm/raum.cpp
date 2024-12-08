#include "raum.h"


raum::raum() {
    std::cout << "Konstruktor der Klasse raum wird aufgerufen!" << std::endl;
    nr = "0.0";
}

raum::raum(std::string neue_nr, unsigned int anz_plaetze, bool hat_beamer) :
    nr(neue_nr), anzahl_sitzplaetze(anz_plaetze), beamer(hat_beamer)
{
    std::cout << "Konstruktor der Klasse raum wird aufgerufen!" << std::endl;
}

void raum::set_raum_nr(std::string nr) { this->nr = nr; }

std::string raum::get_raum_nr() { return nr; }

void raum::set_anzahl_sitzplaetze(unsigned int anzahl_sitzplaetze) {
        this->anzahl_sitzplaetze = anzahl_sitzplaetze; }

unsigned int raum::get_anzahl_sitzplaetze() { return anzahl_sitzplaetze; }

void raum::show_info() {
    std::cout << "Nr : " << nr << std::endl;
    std::cout << "Sitzplatzanzahl : " << anzahl_sitzplaetze << std::endl;
    std::string beamer_str;
    beamer_str = "Achtung! Raum hat keinen Beamer!";
    if (beamer)
        beamer_str = "Der Raum hat einen Beamer / Für Vorträge geeignet!";
    std::cout << "Beamer : " << beamer_str << std::endl;
}
        
