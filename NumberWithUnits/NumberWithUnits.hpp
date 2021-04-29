#include <iostream>
#include <map>
#include <sstream>
using namespace std;

namespace ariel {
    class NumberWithUnits {
    private:
        double _val;
        string _unit;
        static bool unit_pair(const NumberWithUnits& a1, const NumberWithUnits& a2);

    public:
        static void read_units(ifstream &infile);
        NumberWithUnits(double a, const string& u);

        friend NumberWithUnits operator-(const NumberWithUnits& a);
        friend NumberWithUnits operator+(const NumberWithUnits& a);
        friend NumberWithUnits operator+(const NumberWithUnits& a1, const NumberWithUnits& a2);
        friend NumberWithUnits operator-(const NumberWithUnits& a1, const NumberWithUnits& a2);
        
        NumberWithUnits& operator+=(const NumberWithUnits& a2);
        NumberWithUnits& operator-=(const NumberWithUnits& a2);

        /* Boolean operators */
        friend bool operator<(const NumberWithUnits& a1, const NumberWithUnits& a2);
        friend bool operator>(const NumberWithUnits& a1, const NumberWithUnits& a2);
        friend bool operator>=(const NumberWithUnits& a1, const NumberWithUnits& a2);
        friend bool operator<=(const NumberWithUnits& a1, const NumberWithUnits& a2);
        friend bool operator==(const NumberWithUnits& a1, const NumberWithUnits& a2);
        friend bool operator!=(const NumberWithUnits& a1, const NumberWithUnits& a2);
        
        /* ++/-- operators */
        NumberWithUnits& operator++();
        NumberWithUnits operator++(int);
        NumberWithUnits& operator--();
        NumberWithUnits operator--(int);

        /* Multiplication by real number operators */
        friend NumberWithUnits operator*(double d, const NumberWithUnits& a);
        friend NumberWithUnits operator*(const NumberWithUnits& a, double d);
        
        /* Input/Output operators */
        friend ostream& operator<<(ostream& os, const NumberWithUnits& a);
        friend istream& operator>>(istream& s, NumberWithUnits& n);
    };
}