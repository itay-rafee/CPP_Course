#include <iostream>
#include <stdexcept>
#include <math.h>
#include <thread>
#include <chrono>
#include "snowman.hpp"

using namespace std;
// using namespace ariel;

int build_snowman()
{
    int ans = 0;
    int len = 8;
    for (size_t i = 0; i < len; i++)
    {
        ans = ans + pow(10, i) * (rand() % 4 + 1);
    }
    return ans;
}

int main()
{
    int second = 1000;
    int n = 11111111;
    string s = ariel::snowman(n);
    cout << "n = " + to_string(n) + ":" << endl;
    cout << s << endl;

    this_thread::sleep_for(chrono::milliseconds(second));

    n = 22222222;
    s = ariel::snowman(n);
    cout << "\nn = " + to_string(n) + ":" << endl;
    cout << s << endl;

    this_thread::sleep_for(chrono::milliseconds(second));

    n = 33333333;
    s = ariel::snowman(n);
    cout << "\nn = " + to_string(n) + ":" << endl;
    cout << s << endl;

    this_thread::sleep_for(chrono::milliseconds(second));

    n = 44444444;
    s = ariel::snowman(n);
    cout << "\nn = " + to_string(n) + ":" << endl;
    cout << s << endl;
    this_thread::sleep_for(chrono::milliseconds(second));
    int j = 50;
    for (size_t i = 0; i < j; i++)
    {
        n = build_snowman();
        s = ariel::snowman(n);
        cout << "\nn = " + to_string(n) + ":" << endl;
        cout << s << endl;
        this_thread::sleep_for(chrono::milliseconds(second));
    }

    return 0;
}
// g++ -o m snowman.cpp MyMain.cpp