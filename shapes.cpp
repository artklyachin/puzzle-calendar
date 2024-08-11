#include "shapes.h"
#include <iostream>

void test_rotate()
{
    FormStrRepresent other_shape = {"..#",
                                    ".#."};
    Shape res(other_shape);
    res.rotate(0, false);

    for (auto &line : res.cellular_form)
    {
        for (auto &elem : line)
        {
            std::cout << elem << " ";
        }
        std::cout << std::endl;
    }
}

void Shape::rotate(int count_rot90, bool flipped)
{
    auto [n, m] = size();
    size_t new_n = n, new_m = m;
    if (count_rot90 % 2)
    {
        std::swap(new_n, new_m);
    }
    FormType rotated_form = std::vector(new_n, std::vector<int>(new_m, 0));

    for (int row = 0; row < n; ++row)
    {
        for (int column = 0; column < m; ++column)
        {
            int i = row, j = column;
            if (count_rot90 == 1)
            {
                std::tie(i, j) = std::make_pair(j, n - 1 - i);
            }
            else if (count_rot90 == 2)
            {
                std::tie(i, j) = std::make_pair(n - 1 - i, m - 1 - j);
            }
            else if (count_rot90 == 3)
            {
                std::tie(i, j) = std::make_pair(m - 1 - j, i);
            }

            if (flipped)
                j = new_m - 1 - j;
            rotated_form[i][j] = cellular_form[row][column];
        }
    }
    std::swap(cellular_form, rotated_form);
}

bool Table::set_cell(int row, int colomn, CellularForm::CellState state)
{
    auto [n, m] = size();
    if (row < 0 || row >= n)
        return false;
    if (colomn < 0 || colomn >= m)
        return false;

    cellular_form[row][colomn] = (state == CellularForm::CellState::Included ? 1 : 0);
    return true;
}

bool Table::check_nesting(int table_row, int table_colomn, const Shape &shape) const
{
    auto [shape_n, shape_m] = shape.size();
    auto [table_n, table_m] = size();

    if (!(table_row >= 0 && table_row + shape_n <= table_n &&
          table_colomn >= 0 && table_colomn + shape_m <= table_m))
        return false;

    for (int row = 0; row < shape_n; ++row)
    {
        for (int column = 0; column < shape_m; ++column)
        {
            if (shape.get_cell(row, column) == CellularForm::CellState::Included &&
                get_cell(table_row + row, table_colomn + column) == CellularForm::CellState::Included)
            {
                return false;
            }
        }
    }
    return true;
}

bool Table::fill(int table_row, int table_colomn, const Shape &shape)
{
    auto [shape_n, shape_m] = shape.size();
    auto [table_n, table_m] = size();

    if (!check_nesting(table_row, table_colomn, shape))
    {
        return false;
    }

    for (int row = 0; row < shape_n; ++row)
    {
        for (int column = 0; column < shape_m; ++column)
        {
            if (shape.get_cell(row, column) == CellularForm::CellState::Included)
            {
                set_cell(table_row + row, table_colomn + column, CellularForm::CellState::Included);
            }
        }
    }

    return true;
}

bool Table::release(int table_row, int table_colomn, const Shape &shape)
{
    auto [shape_n, shape_m] = shape.size();
    auto [table_n, table_m] = size();

    if (!(table_row >= 0 && table_row + shape_n <= table_n && table_colomn >= 0 && table_colomn + shape_m <= table_m))
        return false;

    for (int row = 0; row < shape_n; ++row)
    {
        for (int column = 0; column < shape_m; ++column)
        {
            if (shape.get_cell(row, column) == CellularForm::CellState::Included)
            {
                set_cell(table_row + row, table_colomn + column, CellularForm::CellState::NotIncluded);
            }
        }
    }

    return true;
}