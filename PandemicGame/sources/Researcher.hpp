#pragma once
#include "City.hpp"
#include "Color.hpp"
#include "Player.hpp"
#include "Board.hpp"

namespace pandemic{

    class Researcher: public Player {

        public:
        Researcher(Board& b, City c):Player(b,c,"Researcher"){};
        Player& discover_cure(Color c) override;
    };
};