#include <iostream>
#include <map>
#include <limits>
#include <string>
#include <cmath>
#include "Board.hpp"
using namespace std;

#include "Direction.hpp"

using ariel::Direction;

namespace ariel
{
    const unsigned int zero = 0, one = 1, two = 2, five = 5, ten = 10;

    void Board::set_min_max(unsigned int row, unsigned int col, Direction n, unsigned int len_s)
    {
        //set minimum
        if (row < min_row)
        {
            min_row = row;
        }
        if (col < min_col)
        {
            min_col = col;
        }

        //set maximum
        if (n == Direction::Vertical)
        {
            if (row + len_s > max_row)
            {
                max_row = row + len_s;
            }
            if (col > max_col)
            {
                max_col = col;
            }
        }
        if (n == Direction::Horizontal)
        {
            if (col + len_s > max_col)
            {
                max_col = col + len_s;
            }
            if (row > max_row)
            {
                max_row = row;
            }
        }
    }

    void Board::set_s_h(unsigned int row, unsigned int col, string s, unsigned int len_s)
    {
        for (size_t i = 0; i < len_s; i++)
        {
            board[row][col] = s.at(i);
            col++;
        }
    }

    void Board::set_s_v(unsigned int row, unsigned int col, string s, unsigned int len_s)
    {
        for (size_t i = 0; i < len_s; i++)
        {
            board[row][col] = s.at(i);
            row++;
        }
    }

    void Board::set_s(unsigned int row, unsigned int col, Direction n, string &s, unsigned int len_s)
    {
        if (n == Direction::Horizontal)
        {
            set_s_h(row, col, s, len_s);
        }
        else
        {
            set_s_v(row, col, s, len_s);
        }
    }

    bool Board::contain(unsigned int row, unsigned int col)
    {
        bool ans = false;
        it1 = board.find(row);
        if (it1 != board.end())
        {
            it2 = board[row].find(col);
            if (it2 != board[row].end())
            {
                ans = true;
            }
        }
        return ans;
    }

    string Board::read_h(unsigned int row, unsigned int col, unsigned int len)
    {
        string ans;
        for (size_t i = 0; i < len; i++)
        {
            if (contain(row, col))
            {
                ans += board[row][col];
            }
            else
            {
                ans += "_";
            }
            col++;
        }
        return ans;
    }

    string Board::read_v(unsigned int row, unsigned int col, unsigned int len)
    {
        string ans;
        for (size_t i = 0; i < len; i++)
        {
            if (contain(row, col))
            {
                ans += board[row][col];
            }
            else
            {
                ans += "_";
            }
            row++;
        }
        return ans;
    }

    unsigned int Board::set_space(unsigned int a)
    {
        unsigned int i = 1;
        while (a / pow(ten, i) >= one)
        {
            i++;
        }
        return i;
    }

    void Board::post(unsigned int row, unsigned int col, Direction n, string s)
    {
        unsigned int len_s = s.size();
        set_min_max(row, col, n, len_s);
        set_s(row, col, n, s, len_s);
    }

    string Board::read(unsigned int row, unsigned int col, Direction n, unsigned int len)
    {
        string ans;
        if (n == Direction::Horizontal)
        {
            ans = read_h(row, col, len);
        }
        else
        {
            ans = read_v(row, col, len);
        }

        return ans;
    }

    void Board::show()
    {
        if (board.empty())
        {
            cout << "1: _________\n2: _________\n3: _________\n4: _________\n5: _________" << endl;
            return;
        }
        unsigned int min_r = min(min_row, min_row - one);
        unsigned int min_c = min(min_col, min_col - two);
        unsigned int max_r = max(max_row, max_row + one);
        unsigned int max_c = max(max_col, max_col + two);
        string ans;
        for (unsigned int i = min_r; i < max_r; ++i)
        {
            unsigned int space = set_space(i);
            ans += to_string(i) + ":";
            for (unsigned int j = space; j < five; ++j)
            {
                ans += " ";
            }
            for (unsigned int j = min_c; j < max_c; ++j)
            {
                if (contain(i, j))
                {
                    ans += board[i][j];
                }
                else
                {
                    ans += "_";
                }
            }
            cout << ans << endl;
            ans = "";
        }
    }
}