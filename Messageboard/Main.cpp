#include <iostream>
#include <string>
#include "Board.hpp"
using namespace std;

#include "Direction.hpp"

using ariel::Direction;
ariel::Board b;

void s()
{
    string fullName;
    cout << "Type your full name: ";
    getline(cin, fullName);
    cout << "Your name is: " << fullName;
}

void save_m()
{
    unsigned int row, col;
    string massage;
    Direction n;
    char d;
    cout << "\nType a row: ";
    cin >> row;
    cout << "\nType a col: ";
    cin >> col;
    cout << "\nType a Direction(h\\v): ";
    cin >> d;
    while (d != 'h' && d != 'v')
    {
        cout << "\nIncorrect input!";
        cout << "\nType a Direction(h\\v): ";
        cin >> d;
    }
    if (d == 'h')
    {
        n = Direction::Horizontal;
    }
    else
    {
        n = Direction::Vertical;
    }

    // cout << "\nType a massage: ";
    char fullName[100];
    cout << "\nType a massage: ";
    cin >> fullName;
    cout << "Your message is: " << fullName;
    massage = fullName;
    b.post(row, col, n, massage);
    cout << "\nMessage saved successfully!\n";
}

void read_m()
{
    unsigned int row, col, len;
    Direction n;
    char d;
    cout << "\nType a row: ";
    cin >> row;
    cout << "\nType a col: ";
    cin >> col;
    cout << "\nType a Direction(h\\v): ";
    cin >> d;
    while (d != 'h' && d != 'v')
    {
        cout << "\nIncorrect input!";
        cout << "\nType a Direction(h\\v): ";
        cin >> d;
    }
    if (d == 'h')
    {
        n = Direction::Horizontal;
    }
    else
    {
        n = Direction::Vertical;
    }

    cout << "\nType a len: ";
    cin >> len;
    cout << b.read(row, col, n, len) << endl;
}

int main()
{
    cout << "\n=== Welcome to Messageboard ===\n";
    char q = 'a';
    // s();
    while (q != 'q')
    {
        cout << "Press 'p' to save message | 'r' read message | 's' show Messageboard | 'q' for exit: ";
        cin >> q;
        switch (q)
        {
        case 'p':
            save_m();
            break;

        case 'r':
            read_m();
            break;

        case 's':
        cout << "\n";
            b.show();
        cout << "\n";

            break;

        default:
            break;
        }
    }
}