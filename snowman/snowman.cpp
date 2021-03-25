#include <iostream>
#include <array>
#include "snowman.hpp"

using namespace std;

//number of the body by order
enum parts
{
    base_num,
    torso_num,
    right_arm_num,
    left_arm_num,
    right_eye_num,
    left_eye_num,
    nose_num,
    hat_num,
    len_legal
};

const int legal_str = 4;
const int ten = 10;

//set the different body types
const array<string, legal_str> hat{" _===_", "  ___\n .....", "   _  \n  /_\\ ", "  ___ \n (_*_)"};
const array<string, legal_str> nose{",", ".", "_", " "};
const array<string, legal_str> left_and_right_eye{".", "o", "O", "-"};
const array<string, legal_str> left_arm_down{"<", " ", "/", " "};
const array<string, legal_str> left_arm_up{" ", "\\", " ", " "};
const array<string, legal_str> right_arm_down{">", " ", "\\", ""};
const array<string, legal_str> right_arm_up{" ", "/", "", ""};
const array<string, legal_str> torso{" : ", "] [", "> <", "   "};
const array<string, legal_str> base{" : ", "\" \"", "___", "   "};

namespace ariel
{
    string str;
    array<int, len_legal> parts{};

    void build_parts(int num)
    {
        // set the number by order to array

        for (size_t i = 0; i < len_legal; i++)
        {
            int part_num = num % ten;
            num /= ten;

            // if the number is 0 or bigger then 4
            if (part_num < 1 || part_num > 4)
            {
                string err = "Invalid code '" + str + "'";
                throw invalid_argument(err);
            }

            parts.at(i) = part_num - 1;
        }
    }

    string build_str()
    {
        string ans;
        ans = hat.at(parts[hat_num]) + "\n" +
              left_arm_up.at(parts[left_arm_num]) + "(" +
              left_and_right_eye.at(parts[left_eye_num]) +
              nose.at(parts[nose_num]) +
              left_and_right_eye.at(parts[right_eye_num]) + ")" +
              right_arm_up.at(parts[right_arm_num]) + "\n" +
              left_arm_down.at(parts[left_arm_num]) + "(" +
              torso.at(parts[torso_num]) + ")" +
              right_arm_down.at(parts[right_arm_num]) + "\n" + " (" +
              base.at(parts[base_num]) + ")";
        return ans;
    }

    string snowman(int num)
    {

        str = to_string(num);
        int str_size = str.size();
        string ans;

        // if the number bigger or smaller then 8
        if (str_size > len_legal || str_size < len_legal)
        {
            string err = "Invalid code '" + str + "'";
            throw invalid_argument(err);
        }
        build_parts(num);
        ans = build_str();
        return ans;
    }
}