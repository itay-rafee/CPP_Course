#include "doctest.h"
#include "Board.hpp"
using namespace ariel;
#include <string>
#include <unistd.h>
using namespace std;

const int n = 100;
const int one = 1;
const int two = 2;
const int ten = 10;
const int alpnum = 63;
const int ten_M = 10 * 100 * 1000;

string gen_random(const int len)
{

    string tmp_s;
    static const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";

    for (int i = 0; i < len; ++i)
    {
        int t = rand() % alpnum;
        tmp_s += alphanum[t];
    }

    return tmp_s;
}

Direction rand_di()
{
    int i = rand() % two;
    if (i == 0)
    {
        return Direction::Horizontal;
    }
    return Direction::Vertical;
}

TEST_CASE("random string")
{
    ariel::Board b;
    for (size_t i = 0; i < n; i++)
    {
        Direction d = rand_di();
        string s1 = gen_random(rand() % ten);
        int len = s1.size();
        unsigned int r = rand() % ten_M;
        unsigned int c = rand() % ten_M;
        b.post(r, c, d, s1);
        string s2 = b.read(r, c, d, len);
        CHECK(s1 == s2);
    }
}

TEST_CASE("Collisions")
{
    ariel::Board b;
    b.post(ten, ten, Direction::Vertical, "123");
    b.post(ten, ten + one, Direction::Vertical, "456");
    b.post(ten, ten + two, Direction::Vertical, "789");
    b.show();
    /* 
    should print:
9:    _______
10:   __147__
11:   __258__
12:   __369__
13:   _______
    */
    b.post(ten + one, ten, Direction::Horizontal, "000");
    b.show();
    /* 
    should print:
9:    _______
10:   __147__
11:   __000__
12:   __369__
13:   _______
    */
    string s1 = "103";
    string s2 = "406";
    string s3 = "709_";
    string s4 = "___";

    string s1_r = b.read(ten, ten, Direction::Vertical, two + one);
    string s2_r = b.read(ten, ten + one, Direction::Vertical, two + one);
    string s3_r = b.read(ten, ten + two, Direction::Vertical, two + two);
    string s4_r = b.read(ten+ten, ten + two, Direction::Vertical, two + one);
    CHECK(s1 == s1_r);
    CHECK(s2 == s2_r);
    CHECK(s3 == s3_r);
    CHECK(s4 == s4_r);
}
