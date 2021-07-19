#include"Virologist.hpp"
using namespace std;

namespace pandemic{

    /* 
      can treat dissis in evrey city in the board 
      by throwing his card
    */
    Player& Virologist::treat(City c){
        if (c == city && board[c] > 0)
        {
            if (board.is_cure_discoverd(c)){board[c] = 0;}
            else{board[c]--;}
        }
        else if(board[c] > 0 && cards.count(c) != 0){
            cards.erase(c);
            if (board.is_cure_discoverd(c)){board[c] = 0;}
            else{board[c]--;}
        }
        else{throw invalid_argument("illigel treat");}
        return *this;
    }
};