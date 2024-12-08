#include "raum.h"


class technikraum : public raum {

    private:

        std::string nutzen;

    public:

        technikraum(std::string nr, unsigned int plaetze, bool beamer, std::string wozu);

        void show_info();
};