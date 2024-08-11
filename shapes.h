#pragma once

#include <map>
#include "cellular_form.h"

class Shape : public CellularForm
{
public:
    Shape(const FormStrRepresent &other_shape) : CellularForm(other_shape) {};

    void rotate(int count_rot90, bool flipped);

private:
    friend void test_rotate();
};


class Table : public CellularForm
{
public:
    Table(const FormStrRepresent &other_shape) : CellularForm(other_shape) {};

    bool set_cell(int row, int colomn, CellularForm::CellState state);

    bool check_nesting(int row, int colomn, const Shape& shape) const;
    bool fill(int row, int colomn, const Shape& shape);
    bool release(int row, int colomn, const Shape& shape);
};
