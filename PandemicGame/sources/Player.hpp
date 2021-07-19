#pragma once
#include "Board.hpp"
#include "City.hpp"
#include "Color.hpp"
#include <set>

namespace pandemic
{

    class Player
    {
    protected:
        City city;
        std::set<City> cards;
        std::set<Color> meditions;
        std::string rol;

    public:
        Board& board;

        Player(Board &b, City c, std::string r = "Player") : board(b), city(c), rol(r){};

        Player &take_card(City c);
        Player &drive(City c);
        Player &fly_charter(City c);
        Player &fly_shuttle(City c);
        std::string role(){return rol;};
        
        /* Virtual Method */
        virtual Player &fly_direct(City c);
        virtual Player &build();
        virtual Player &discover_cure(Color c);
        virtual Player &treat(City c);
        virtual void fly(City c){}; // method for Medic

        /* Method for the main */
        City &get_curr_location(){return city;} 
        auto get_cards()const{return cards;}
    };
};