// Include Guard
#ifndef _RAUM_H
#define _RAUM_H

#include <string>
#include <iostream>

class raum {

    protected:
        std::string         nr;
        unsigned int        anzahl_sitzplaetze;
        bool                beamer;

    public:

        raum();

        raum(std::string neue_nr, unsigned int anz_plaetze, bool hat_beamer);

        void set_raum_nr(std::string nr);
        std::string get_raum_nr();

        void set_anzahl_sitzplaetze(unsigned int anzahl_sitzplaetze);

        unsigned int get_anzahl_sitzplaetze();

        void show_info();
        
};

#endif