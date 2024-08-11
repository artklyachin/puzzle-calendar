#include "game_table.h"
#include <iostream>

#define DEBUG 1

GameTable::GameTable(FormStrRepresent str_repr_table, const std::map<char, FormStrRepresent> &str_repr_shapes)
    : table(str_repr_table), dates(std::vector<std::vector<int>>(31, std::vector<int>(12, 0)))
{
    create_all_shapes(str_repr_shapes);
    insert_shapes_starting_from_index(0);
}

void GameTable::create_all_shapes(const std::map<char, FormStrRepresent> &str_repr_shapes)
{
    for (auto &[name, elem] : str_repr_shapes)
    {
        Shape shape(elem);

        Shape rot90_shape(shape);
        rot90_shape.rotate(1, false);
        bool rot90_coincid = (rot90_shape == shape);

        Shape rot180_shape(shape);
        rot180_shape.rotate(2, false);
        bool rot180_coincid = (rot180_shape == shape);

        Shape flipped_shape(shape);
        flipped_shape.rotate(0, true);
        bool flipped_coincid = (flipped_shape == shape || name == 'V');

        int rotate_count;
        if (rot90_coincid)
        {
            rotate_count = 1;
        }
        else if (rot180_coincid)
        {
            rotate_count = 2;
        }
        else
        {
            rotate_count = 4;
        }

        for (int i = 0; i < rotate_count; ++i)
        {
            Shape rot_shape(shape);
            rot_shape.rotate(i, false);
            shapes[name].push_back(rot_shape);

            if (!flipped_coincid)
            {
                Shape rot_flip_shape(shape);
                rot_flip_shape.rotate(i, true);
                shapes[name].push_back(rot_flip_shape);
            }
        }
    }
}

bool GameTable::insert_shapes_starting_from_index(int index)
{
    if (index == shapes_names.size()) {
        int date = -1, month = -1;

        for (int i = 0; i < 2; ++i) {
            for (int j = 0; j < 6; ++j) {
                if (table.get_cell(i, j) == CellularForm::CellState::NotIncluded) {
                    month = i * 6 + j;
                }
            }
        }
        for (int i = 0; i < 5; ++i) {
            for (int j = 0; j < (i == 4 ? 3 : 7); ++j) {
                if (table.get_cell(i + 2, j) == CellularForm::CellState::NotIncluded) {
                    date = i * 7 + j;
                }
            }
        }
        if (date != -1 && month != -1) {
            ++dates[date][month];
        }
        return true;
    }

    auto [n, m] = table.size();
    char name = shapes_names[index];

    for (int shape_num = 0; shape_num < shapes[name].size(); ++shape_num)
    {
        if (index == 1) {
            std::cout << name << " num: " << shape_num << std::endl;
        }

        auto &shape = shapes[name][shape_num];
        auto [shape_n, shape_m] = shape.size();
        for (int row = 0; row <= n - shape_n; ++row)
        {
            for (int column = 0; column <= m - shape_m; ++column)
            {
#ifdef DEBUG
                if (index == 0)
                {
                    std::cout << name << " row column: " << row << " " << column << std::endl;
                }
#endif
                if (table.check_nesting(row, column, shape))
                {

                    shapes_answer_coordinate.emplace_back(std::make_pair(row, column), name, shape_num); // insert shape
                    table.fill(row, column, shape);

                    insert_shapes_starting_from_index(index + 1);

                    shapes_answer_coordinate.pop_back(); // delete shape
                    table.release(row, column, shape);
                }
            }
        }
    }
    return false;
}

void GameTable::print_solition()
{
    for (int i = 0; i < 12; ++i) {
        for (int j = 0; j < 31; ++j) {
            std::cout << "date month: " << j + 1 << " " << i + 1 << " : " << dates[j][i] << std::endl; 
        }
    }
}