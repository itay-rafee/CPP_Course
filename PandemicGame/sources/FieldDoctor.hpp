#pragma once
#include "City.hpp"
#include "Color.hpp"
#include "Player.hpp"
#include "Board.hpp"

namespace pandemic{

    class FieldDoctor: public Player {

        public:
        FieldDoctor(Board& b, City c):Player(b,c,"FieldDoctor"){};
        Player &treat(City c) override;
    };
};