#include "GeneSplicer.hpp"
#include <array>
using namespace std;
const int for_discover_cure = 5;

namespace pandemic
{

    /* can discover cure with card that not in the same color */ 
    Player &GeneSplicer::discover_cure(Color c)
    {
        if (meditions.count(c) != 0)
        {
            return *this;
        }

        if (!board.is_research_station(city))
        {
            throw invalid_argument("Not research station");
        }

        size_t i = 0;
        for (const auto &card : cards){i++;}
        if (i < for_discover_cure){throw invalid_argument("Not enough cards");}
        i=0;
        for (auto it = cards.begin(); it != cards.end(); i++)
        {
            if (i == for_discover_cure){break;}
            {it = cards.erase(it);}
        }
        board.mark_cured(c);
        meditions.insert(c);
        return *this;
    }
};