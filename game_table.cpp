#include "game_table.h"
#include <iostream>

GameTable::GameTable(FormStrRepresent str_repr_table, const std::map<char, FormStrRepresent> &str_repr_shapes)
    : table(str_repr_table)
{
    create_all_shapes(str_repr_shapes);
    solution_has_found = insert_shapes_starting_from_index(0);
}

void GameTable::create_all_shapes(const std::map<char, FormStrRepresent> &str_repr_shapes)
{
    for (auto &[name, elem] : str_repr_shapes)
    {
        shapes_names.push_back(name);

        Shape shape(elem);

        Shape rot90_shape(shape);
        rot90_shape.rotate(1, false);
        bool rot90_coincid = (rot90_shape == shape);

        Shape rot180_shape(shape);
        rot180_shape.rotate(2, false);
        bool rot180_coincid = (rot180_shape == shape);

        Shape flipped_shape(shape);
        flipped_shape.rotate(0, true);
        bool flipped_coincid = (flipped_shape == shape);

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
    if (index == shapes_names.size())
        return true;

    auto [n, m] = table.size();
    char name = shapes_names[index];

    for (int shape_num = 0; shape_num < shapes[name].size(); ++shape_num)
    {
        auto &shape = shapes[name][shape_num];
        for (int row = 0; row < n; ++row)
        {
            for (int column = 0; column < m; ++column)
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

                    // solution_has_found = true;
                    // print_solition();
                    // std::cout << std::endl;

                    if (insert_shapes_starting_from_index(index + 1))
                    {
                        return true;
                    }

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
    if (!solution_has_found)
    {
        std::cout << "solution has not found." << std::endl;
        return;
    }

    auto [table_n, table_m] = table.size();
    std::vector<std::vector<char>> output_table(table_n, std::vector<char>(table_m, '.'));

    for (auto [bound, shape_name, shape_num] : shapes_answer_coordinate)
    {
        auto [upper_bound, left_bound] = bound;
        auto &shape = shapes[shape_name][shape_num];
        auto [shape_n, shape_m] = shape.size();

        for (int row = 0; row < shape_n; ++row)
        {
            for (int column = 0; column < shape_m; ++column)
            {
                if (shape.get_cell(row, column) == CellularForm::CellState::Included)
                {
                    output_table[upper_bound + row][left_bound + column] = shape_name;
                }
            }
        }
    }

    for (int row = 0; row < table_n; ++row)
    {
        for (int column = 0; column < table_m; ++column)
        {
            std::cout << output_table[row][column] << " ";
        }
        std::cout << std::endl;
    }
}