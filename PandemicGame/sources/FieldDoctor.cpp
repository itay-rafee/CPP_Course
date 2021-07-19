#include"FieldDoctor.hpp"
#include <iostream>
#include <sstream>

using namespace std;
using namespace pandemic;

namespace pandemic{

    /* can do treat also for the neighbor */
    Player& FieldDoctor::treat(City c){
        if ((c == city || Board::is_connected(city, c)) && board[c] > 0)
        {
            if (board.is_cure_discoverd(c)){board[c] = 0;}
            else{board[c]--;}
            return *this;
        }
        throw invalid_argument("illigel treat");
    }
};