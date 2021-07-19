#include"Medic.hpp"
using namespace std;

namespace pandemic{

    /* treat method take all the cubes of diseas. */
    Player& Medic::treat(City c){
        if (c == city && board[c] > 0)
        {
            board[c] = 0;
            return *this;
        }
        throw invalid_argument("illigel treat");
    }

    /* In every city he goes, 
       if there is cure discoverd he take all the cubes of diseas */
    void Medic::fly(City c){
        if (board.is_cure_discoverd(c)){board[c] = 0;}
    }
};