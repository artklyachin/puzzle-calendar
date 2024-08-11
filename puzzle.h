#include <iostream>
#include <map>
#include <vector>
#include <string>
#include "game_table.h"

class CalendarPuzzel {
public:
    void print_one_solution(int date, int month);

private:
    FormStrRepresent str_repr_table = {
            "......x",
            "......x",
            ".......",
            ".......",
            ".......",
            ".......",
            "...xxxx",
    };

    std::map<char, FormStrRepresent> str_repr_shapes = {
        {'V', {
                        "x..",
                        "x..",
                        "xxx",
                }},
        {'P', {
                        "xxx",
                        "xx.",
                }},
        {'Z', {
                        "xx.",
                        ".x.",
                        ".xx",
                }},
        {'L', {
                        "xxxx",
                        "x...",
                }},
        {'N', {
                        "xx..",
                        ".xxx",
                }},
        {'O', {
                        "xxx",
                        "xxx",
                }},
        {'Y', {
                        "xxxx",
                        ".x..",
                }},
        {'U', {
                        "xxx",
                        "x.x",
                }}
    };
};