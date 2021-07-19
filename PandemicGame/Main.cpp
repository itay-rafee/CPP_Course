#include "Board.hpp"
#include "Dispatcher.hpp"
#include "Researcher.hpp"
#include "Scientist.hpp"
#include "OperationsExpert.hpp"
#include "Virologist.hpp"
#include "FieldDoctor.hpp"
#include "GeneSplicer.hpp"
#include "Medic.hpp"

using namespace pandemic;

#include <iostream>
#include <stdexcept>
using namespace std;

const int numOfCities = 48;
const int maxCubesNum = 20;
const int numOfCards = 5;
/*
This demo is actual two player pandemic game
without any gui, just the console
*/
const int randInt(int max, int min = 0)
{
    int range = max - min + 1;
    return (const int)(rand() % range + min);
}

City rand_city()
{
    return (City)((rand() + 1) % numOfCities);
}

Player *createPlayer(Board &board)
{
    int choice = 0;
    cout << "Select a Player you want to be:" << endl;
    cout << "1 - Medic | 2 - Dispatcher | 3 - Field Doctor" << endl;
    cout << "4 - Gene Splicer | 5 - Operation Expert | 6 - Researcher" << endl;
    cout << "7 - Virologist | 8 - Scientist" << endl;
    cin >> choice;
    Player *player;
    switch (choice)
    {
    case 1:
        player = new Medic{board, rand_city()};
        break;
    case 2:
        player = new Dispatcher{board, rand_city()};
        break;
    case 3:
        player = new FieldDoctor{board, rand_city()};
        break;
    case 4:
        player = new GeneSplicer{board, rand_city()};
        break;
    case 5:
        player = new OperationsExpert{board, rand_city()};
        break;
    case 6:
        player = new Researcher{board, rand_city()};
        break;
    case 7:
        player = new Virologist{board, rand_city()};
        break;
    case 8:
        player = new Scientist{board, rand_city()};
        break;
    default:
        cout << "Invalid Choice!!!!" << endl
             << "Picked Operation Expert By default" << endl;
        return new OperationsExpert{board, rand_city()};
    }
    return player;
}


City input_city(Player *player)
{
    string dest_city;
    cout << "you are now in " << Board::city_to_string(player->get_curr_location()) << endl;
    cout << "What's your destantion: " << endl;
    cin >> dest_city; //assume right input
    return Board::string_to_city(dest_city);
}

Color input_disease_color()
{
    string color;
    cout << "Select a disease color: " << endl;
    cin >> color;
    return Board::string_to_color(color);
}

void print_owned_cards(Player *player)
{
    cout << "\nWe are in: " << Board::city_to_string(player->get_curr_location()) << endl;
    cout << "Our cards:  " << endl;
    for (City card : player->get_cards())
    {
        cout << Board::city_to_string(card) << " , ";
    }
    cout << endl;
}

bool perform_action(Player *player)
{
    int action_choice = 0;
    print_owned_cards(player);
    cout << "\n\nSelect an action to perform: " << endl;
    cout << "1 - take card from the deck | 2 - drive" << endl;
    cout << "3 - fly direct | 4 - fly shuttle | 5 - fly charter" << endl;
    cout << "6 - build | 7 - discover cure | 8 - treat | 9 - print board" << endl;
    cout << "0 - exit" << endl;
    cout << "Action you select: ";
    cin >> action_choice;
    cout << endl;
    try
    {
        switch (action_choice)
        {
        case 1:
            player->take_card(rand_city());
            break;
        case 2:
            player->drive(input_city(player));
            break;
        case 3:
            player->fly_direct(input_city(player));
            break;
        case 4:
            player->fly_shuttle(input_city(player));
            break;
        case 5:
            player->fly_charter(input_city(player));
            break;
        case 6:
            player->build();
            break;
        case 7:
            player->discover_cure(input_disease_color());
            break;
        case 8:
            player->treat(input_city(player));
            break;
        case 0:
            cout << "Goodbye" << endl;
            return false;
        case 9:
            cout << player->board << endl;
            break;
        default:
            cout << "No such action" << endl;
            break;
        }
    }
    catch (const exception &e)
    {
        cout << e.what() << endl;
    }
    return true;
}
int main()
{
    Board board;
    for (int i = 0; i < numOfCities; i++)
    {
        board[(City)i] = randInt(maxCubesNum);
    }
    cout << "\t =============================== \n";
    cout << "\t          Pandemic Game          \n";
    cout << "\t =============================== \n\n";
    Player *player = createPlayer(board);
    cout << "You Pick: " << player->role() << endl;
    bool t = true;
    while (t){t = perform_action(player);}
    delete player;
}