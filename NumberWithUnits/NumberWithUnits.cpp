#include "NumberWithUnits.hpp"
#include <iostream>
#include <map>
#include <fstream>   // ifstream
#include <sstream>   // stringstream
#include <algorithm> // remove_if
using namespace std;

const double eps = 0.0001;
static map<string,map<string,double>> units_sign;

namespace ariel
{
    bool NumberWithUnits::unit_pair(const NumberWithUnits &a1, const NumberWithUnits &a2)
    {
        return units_sign.count(a1._unit) != 0 &&
               units_sign[a1._unit].count(a2._unit) != 0;
    }

    NumberWithUnits::NumberWithUnits(double a, const string& u)
    {
        if (units_sign.count(u)==0)
        {
            throw invalid_argument("Illegal units!");
        }
        _unit = u;
        _val = a;
    };

    /* Read_units method */
    void set_neighbors(string &u1, string &u2, double n1, double n2)
    {
        for (const auto &myPair : units_sign[u2])
        {
            units_sign[u1][myPair.first] = n2 * myPair.second;
            units_sign[myPair.first][u1] = n1 / myPair.second;
        }
    }

    void NumberWithUnits::read_units(ifstream &infile)
    {
        double n1 = 1;
        double n2 = 0;
        string u1;
        string u2;
        string line;
        while (getline(infile, line))
        {
            line.erase(remove_if(line.begin(), line.end(), ::isspace), line.end());
            size_t delim = 1;
            while (delim < line.length() && line[delim] != '='){delim++;}
            u1 = line.substr(1, delim - 1);
            stringstream ss(line.substr(delim + 1, line.length() - 1));
            ss >> n2 >> u2;
            set_neighbors(u1, u2, n1 / n2, n2);
            set_neighbors(u2, u1, n2, n1 / n2);

            units_sign[u1][u2] = n2;
            units_sign[u2][u1] = n1 / n2;
            if (units_sign[u1].count(u1) == 0){units_sign[u1][u1] = 1;}
            if (units_sign[u2].count(u2) == 0){units_sign[u2][u2] = 1;}
        }
    };

    /* Arithmetic operators */
    NumberWithUnits operator-(const NumberWithUnits &a)
    {
        return NumberWithUnits(-a._val, a._unit);
    }

    NumberWithUnits operator+(const NumberWithUnits &a)
    {
        return a;
    }

    NumberWithUnits operator+(const NumberWithUnits &a1, const NumberWithUnits &a2)
    {
        if (NumberWithUnits::unit_pair(a1, a2))
        {
            double a2_new_amount = a2._val * units_sign[a2._unit][a1._unit];
            return NumberWithUnits(a1._val + a2_new_amount, a1._unit);
        }
        throw invalid_argument("not same unit");
    }

    NumberWithUnits operator-(const NumberWithUnits &a1, const NumberWithUnits &a2)
    {
        if (NumberWithUnits::unit_pair(a1, a2))
        {
            double a2_new_amount = a2._val * units_sign[a2._unit][a1._unit];
            return NumberWithUnits(a1._val - a2_new_amount, a1._unit);
        }
        throw invalid_argument("not same unit");
    }

    NumberWithUnits &NumberWithUnits::operator+=(const NumberWithUnits &a2)
    {
        if (NumberWithUnits::unit_pair(*this, a2))
        {
            double a2_new_amount = a2._val * units_sign[a2._unit][this->_unit];
            this->_val += a2_new_amount;
            return *this;
        }
        throw invalid_argument("not same unit");
    }
    NumberWithUnits &NumberWithUnits::operator-=(const NumberWithUnits &a2)
    {
        if (NumberWithUnits::unit_pair(*this, a2))
        {
            double a2_new_amount = a2._val * units_sign[a2._unit][this->_unit];
            this->_val -= a2_new_amount;
            return *this;
        }
        throw invalid_argument("not same unit");
    }

    /* Boolean operators */
    bool operator<(const NumberWithUnits &a1, const NumberWithUnits &a2)
    {
        if (NumberWithUnits::unit_pair(a1, a2))
        {
            double a2_new_amount = a2._val * units_sign[a2._unit][a1._unit];
            return (a1._val < a2_new_amount);
        }
        throw invalid_argument("not same unit");
    }

    bool operator>(const NumberWithUnits &a1, const NumberWithUnits &a2)
    {
        return (a2 < a1);
    }

    bool operator>=(const NumberWithUnits &a1, const NumberWithUnits &a2)
    {
        return !(a1 < a2);
    }

    bool operator<=(const NumberWithUnits &a1, const NumberWithUnits &a2)
    {
        return !(a2 < a1);
    }

    bool operator==(const NumberWithUnits &a1, const NumberWithUnits &a2)
    {
        if (NumberWithUnits::unit_pair(a1, a2))
        {
            double a2_new_amount = a2._val * units_sign[a2._unit][a1._unit];
            return (abs(a1._val - a2_new_amount) <= eps);
        }
        throw invalid_argument("not same unit");
    }

    bool operator!=(const NumberWithUnits &a1, const NumberWithUnits &a2)
    {return !(a1 == a2);}

    /* ++/-- operators */
    NumberWithUnits &NumberWithUnits::operator++() // prefix increment
    {
        this->_val++;
        return *this;
    }
    NumberWithUnits NumberWithUnits::operator++(int) // postfix increment
    {
        NumberWithUnits copy = *this;
        this->_val++;
        return copy;
    }
    NumberWithUnits &NumberWithUnits::operator--() // prefix increment
    {
        this->_val--;
        return *this;
    }
    NumberWithUnits NumberWithUnits::operator--(int) // postfix increment
    {
        NumberWithUnits copy = *this;
        this->_val--;
        return copy;
    }

    /* Multiplication by real number operators */
    NumberWithUnits operator*(double d, const NumberWithUnits &a)
    {
        return NumberWithUnits(d * a._val, a._unit);
    }

    NumberWithUnits operator*(const NumberWithUnits &a, double d)
    {
        return NumberWithUnits(d * a._val, a._unit);
    }

    /* Input/Output operators */
    ostream &operator<<(ostream &os, const NumberWithUnits &a)
    {
        os << a._val << "[" << a._unit << "]";
        return os;
    }

    istream &operator>>(istream &s, NumberWithUnits &n)
    {
        char c = 0;
        string t;
        double v = 0;
        s >> v >> c >> t >> c;
        if (t[t.length() - 1] == ']'){t.pop_back();}
        if (c == '-'){s.putback('-');}
        if(units_sign.count(t) != 0){
            n._val = v;
            n._unit = t;
            return s;
        }
        throw invalid_argument(t + " is not a valid unit!");
    }
}