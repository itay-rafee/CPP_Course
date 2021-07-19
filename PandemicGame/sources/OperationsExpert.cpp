#include "OperationsExpert.hpp"

namespace pandemic{

    /*
        can build in every city research station
        without throw any card.
    */
    Player& OperationsExpert::build(){
        if (!board.is_research_station(city)){board.build_research_station(city);}
        return *this;
    }
};