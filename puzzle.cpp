#include "puzzle.h"
#include <iostream>

void CalendarPuzzel::print_one_solution()
{
    FormStrRepresent gaming_str_repr_table = str_repr_table;

    GameTable game_table(gaming_str_repr_table, str_repr_shapes);
    game_table.print_solition();
}
