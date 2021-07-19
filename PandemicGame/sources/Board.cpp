#include "City.hpp"
#include "Color.hpp"
#include "Board.hpp"
#include <map>
#include <set>
#include <iostream>
#include <algorithm>
#include <iomanip> // setw(), setfill(), left (or right).

using namespace std;

namespace pandemic
{
    /* Remove all the cures from the board */
    void Board::remove_cures() {medicines.clear();}

    /* check how many cubes of diseas there is to city*/
    int &Board::operator[](City c){return cubesOfDiseas[c];}
    
    /* check if there isn't cubes of diseas */
    bool Board::is_clean()
    {
        for (auto &dis : cubesOfDiseas)
        {
            if (dis.second > 0){return false;}
        }
        return true;
    }

    /* check if 'c1' connecred to 'c2' */
    bool Board::is_connected(City &c1, City &c2)
    {
        if (neighbors.count(c1) != 0)
        {
            if (neighbors[c1].count(c2) != 0){return true;}
        }
        return false;
    }

    /* build research station for the city */
    void Board::build_research_station(City c) 
    {
        researchStations.insert(c);
    }

    /* check if there is research station for the city */
    bool Board::is_research_station(City c)
    {
        return researchStations.count(c) != 0;
    }

    /* mark cured for the color */
    void Board::mark_cured(Color c){medicines.insert(c);}

    /* check if the cure is discoverd for the city */
    bool Board::is_cure_discoverd(City c)
    {
        return medicines.count(color_of(c)) != 0;
    }

    /* return the color of the city */
    Color Board::color_of(City c) { return city_color.at(c); }

    /* << Operator Implementation */
    std::ostream &operator<<(std::ostream &os,const Board &b)
    {
        const char separator   = ' ';
        const char lineSign    = '=';
        const int nameWidth    = 13;
        const int numWidth     = 3;
        const int lineWidth    = 55;
        os << left << setw(lineWidth) << setfill(lineSign) << "" << endl;
        int counter = 0;
        for (const auto &p : Board::cities_names) {
            os << left << setw(nameWidth) << setfill(separator) << p.first << ":" << setw(numWidth) << setfill(separator) << b.cubesOfDiseas.at(p.second) << "| ";
            if ((++counter)%3==0) {os << endl;}
        }
        os << left << setw(lineWidth) << setfill(lineSign) << "" << endl;
        string total_details = "Research Stations: " + to_string(b.researchStations.size()) + ". Medicines: " + to_string(b.medicines.size());
        os << left << setw(lineWidth) << setfill(separator) << total_details << endl;
        os << left << setw(lineWidth) << setfill(lineSign) << "" << endl;
        return os;    
    }


    /* =============================== */
    /*   method for the Main program   */
    /* =============================== */
    
    
    /* get string and returned the city */
    City Board::string_to_city(const string &city_name)
    {
        return cities_names.find(city_name)->second;
    }

    /* get city and returned the string */
    string Board::city_to_string(City city)
    {
        return find_if(begin(Board::cities_names), end(Board::cities_names), [&](const auto &element)
                       { return element.second == city; })
            ->first;
    }

    /* get string and returned the color */
    Color Board::string_to_color(const string &color_name)
    {
        return colors_names.find(color_name)->second;
    }

    map<City, set<City>> Board::neighbors{
        {Algiers, {Madrid, Paris, Istanbul, Cairo}},
        {Atlanta, {Chicago, Miami, Washington}},
        {Baghdad, {Tehran, Istanbul, Cairo, Riyadh, Karachi}},
        {Bangkok, {Kolkata, Chennai, Jakarta, HoChiMinhCity, HongKong}},
        {Beijing, {Shanghai, Seoul}},
        {Bogota, {MexicoCity, Lima, Miami, SaoPaulo, BuenosAires}},
        {BuenosAires, {Bogota, SaoPaulo}},
        {Cairo, {Algiers, Istanbul, Baghdad, Khartoum, Riyadh}},
        {Chennai, {Mumbai, Delhi, Kolkata, Bangkok, Jakarta}},
        {Chicago, {SanFrancisco, LosAngeles, MexicoCity, Atlanta, Montreal}},
        {Delhi, {Tehran, Karachi, Mumbai, Chennai, Kolkata}},
        {Essen, {London, Paris, Milan, StPetersburg}},
        {HoChiMinhCity, {Jakarta, Bangkok, HongKong, Manila}},
        {HongKong, {Bangkok, Kolkata, HoChiMinhCity, Shanghai, Manila, Taipei}},
        {Istanbul, {Milan, Algiers, StPetersburg, Cairo, Baghdad, Moscow}},
        {Jakarta, {Chennai, Bangkok, HoChiMinhCity, Sydney}},
        {Johannesburg, {Kinshasa, Khartoum}},
        {Karachi, {Tehran, Baghdad, Riyadh, Mumbai, Delhi}},
        {Khartoum, {Cairo, Lagos, Kinshasa, Johannesburg}},
        {Kinshasa, {Lagos, Khartoum, Johannesburg}},
        {Kolkata, {Delhi, Chennai, Bangkok, HongKong}},
        {Lagos, {SaoPaulo, Khartoum, Kinshasa}},
        {Lima, {MexicoCity, Bogota, Santiago}},
        {London, {NewYork, Madrid, Essen, Paris}},
        {LosAngeles, {SanFrancisco, Chicago, MexicoCity, Sydney}},
        {Madrid, {London, NewYork, Paris, SaoPaulo, Algiers}},
        {Manila, {Taipei, SanFrancisco, HoChiMinhCity, Sydney, HongKong}},
        {MexicoCity, {LosAngeles, Chicago, Miami, Lima, Bogota}},
        {Miami, {Atlanta, MexicoCity, Washington, Bogota}},
        {Milan, {Essen, Paris, Istanbul}},
        {Montreal, {Chicago, Washington, NewYork}},
        {Moscow, {StPetersburg, Istanbul, Tehran}},
        {Mumbai, {Karachi, Delhi, Chennai}},
        {NewYork, {Montreal, Washington, London, Madrid}},
        {Osaka, {Taipei, Tokyo}},
        {Paris, {Algiers, Essen, Madrid, Milan, London}},
        {Riyadh, {Baghdad, Cairo, Karachi}},
        {SanFrancisco, {LosAngeles, Chicago, Tokyo, Manila}},
        {Santiago, {Lima}},
        {SaoPaulo, {Bogota, BuenosAires, Lagos, Madrid}},
        {Seoul, {Beijing, Shanghai, Tokyo}},
        {Shanghai, {Beijing, HongKong, Taipei, Seoul, Tokyo}},
        {StPetersburg, {Essen, Istanbul, Moscow}},
        {Sydney, {Jakarta, Manila, LosAngeles}},
        {Taipei, {Shanghai, HongKong, Osaka, Manila}},
        {Tehran, {Baghdad, Moscow, Karachi, Delhi}},
        {Tokyo, {Seoul, Shanghai, Osaka, SanFrancisco}},
        {Washington, {Atlanta, NewYork, Montreal, Miami}}};

    map<City, Color> Board::city_color{
        {Algiers, Black},
        {Atlanta, Blue},
        {Baghdad, Black},
        {Bangkok, Red},
        {Beijing, Red},
        {Bogota, Yellow},
        {BuenosAires, Yellow},
        {Cairo, Black},
        {Chennai, Black},
        {Chicago, Blue},
        {Delhi, Black},
        {Essen, Blue},
        {HoChiMinhCity, Red},
        {HongKong, Red},
        {Istanbul, Black},
        {Jakarta, Red},
        {Johannesburg, Yellow},
        {Karachi, Black},
        {Khartoum, Yellow},
        {Kinshasa, Yellow},
        {Kolkata, Black},
        {Lagos, Yellow},
        {Lima, Yellow},
        {London, Blue},
        {LosAngeles, Yellow},
        {Madrid, Blue},
        {Manila, Red},
        {MexicoCity, Yellow},
        {Miami, Yellow},
        {Milan, Blue},
        {Montreal, Blue},
        {Moscow, Black},
        {Mumbai, Black},
        {NewYork, Blue},
        {Osaka, Red},
        {Paris, Blue},
        {Riyadh, Black},
        {SanFrancisco, Blue},
        {Santiago, Yellow},
        {SaoPaulo, Yellow},
        {Seoul, Red},
        {Shanghai, Red},
        {StPetersburg, Blue},
        {Sydney, Red},
        {Taipei, Red},
        {Tehran, Black},
        {Tokyo, Red},
        {Washington, Blue}};

    map<string, Color> Board::colors_names{
        {"Black", Color::Black},
        {"Blue", Color::Blue},
        {"Red", Color::Red},
        {"Yellow", Color::Yellow}};

    map<string, City> Board::cities_names = {
        {"Algiers", City::Algiers},
        {"Atlanta", City::Atlanta},
        {"Baghdad", City::Baghdad},
        {"Bangkok", City::Bangkok},
        {"Beijing", City::Beijing},
        {"Bogota", City::Bogota},
        {"BuenosAires", City::BuenosAires},
        {"Cairo", City::Cairo},
        {"Chennai", City::Chennai},
        {"Chicago", City::Chicago},
        {"Delhi", City::Delhi},
        {"Essen", City::Essen},
        {"HoChiMinhCity", City::HoChiMinhCity},
        {"HongKong", City::HongKong},
        {"Istanbul", City::Istanbul},
        {"Jakarta", City::Jakarta},
        {"Johannesburg", City::Johannesburg},
        {"Karachi", City::Karachi},
        {"Khartoum", City::Khartoum},
        {"Kinshasa", City::Kinshasa},
        {"Kolkata", City::Kolkata},
        {"Lagos", City::Lagos},
        {"Lima", City::Lima},
        {"London", City::London},
        {"LosAngeles", City::LosAngeles},
        {"Madrid", City::Madrid},
        {"Manila", City::Manila},
        {"MexicoCity", City::MexicoCity},
        {"Miami", City::Miami},
        {"Milan", City::Milan},
        {"Montreal", City::Montreal},
        {"Moscow", City::Moscow},
        {"Mumbai", City::Mumbai},
        {"NewYork", City::NewYork},
        {"Osaka", City::Osaka},
        {"Paris", City::Paris},
        {"Riyadh", City::Riyadh},
        {"SanFrancisco", City::SanFrancisco},
        {"Santiago", City::Santiago},
        {"SaoPaulo", City::SaoPaulo},
        {"Seoul", City::Seoul},
        {"Shanghai", City::Shanghai},
        {"StPetersburg", City::StPetersburg},
        {"Sydney", City::Sydney},
        {"Taipei", City::Taipei},
        {"Tehran", City::Tehran},
        {"Tokyo", City::Tokyo},
        {"Washington", City::Washington},
    };
};
