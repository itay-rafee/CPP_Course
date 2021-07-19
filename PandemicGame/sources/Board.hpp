#pragma once
#include "City.hpp"
#include "Color.hpp"
#include <map>
#include <set>
#include <iostream>

namespace pandemic {

    class Board {
        private:
        std::map<City, int> cubesOfDiseas;
        std::set<City> researchStations;
        std::set<Color> medicines;
        static std::map<City, std::set<City>> neighbors;
        static std::map<City, Color> city_color;
       
        /* map for the main function */
        static std::map<std::string, Color> colors_names;
        static std::map<std::string, City> cities_names;
        
        public:
            Board() {}

            int& operator[](City c);
            void remove_cures();
            void mark_cured(Color c);
            void build_research_station(City c);
            bool is_clean();
            bool is_research_station(City c);
            bool is_cure_discoverd(City c);
            static bool is_connected(City& c1, City& c2);
            static Color color_of(City c);
            friend std::ostream& operator<<(std::ostream& os,const Board& b);

            /* Method for the main */
            static City string_to_city(const std::string&);
            static std::string city_to_string(City);
            static Color string_to_color(const std::string&);
    };



}