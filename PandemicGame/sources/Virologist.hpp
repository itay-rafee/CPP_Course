#pragma once
#include "City.hpp"
#include "Color.hpp"
#include "Player.hpp"
#include "Board.hpp"

namespace pandemic
{

    class Virologist
        : public Player
    {

    public:
        Virologist(Board& b, City c) : Player(b, c,"Virologist"){};
        Player &treat(City c) override;
    };
};