#include "raum.h"

class hoersaal : public raum {

    private:

        bool tafel;
        bool mikro;

    public:

        hoersaal(std::string nr, unsigned int plaetze, bool beamer, bool hat_tafel, bool hat_mikro);

        void show_info();

};