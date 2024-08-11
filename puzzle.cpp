#include "puzzle.h"
#include <iostream>

void CalendarPuzzel::print_one_solution(int date, int month) {
    if (!(date >= 1 && date <= 31 && month >= 1 && month <= 12)) {
        std::cout << "error: incorrect date or month" << std::endl;
        return;
    }

    FormStrRepresent gaming_str_repr_table = str_repr_table;

    --date;
    --month;
    gaming_str_repr_table[month / 6][month % 6] = 'x';
    gaming_str_repr_table[date / 7 + 2][date % 7] = 'x';

    GameTable game_table(gaming_str_repr_table, str_repr_shapes);
    game_table.print_solition();
}
