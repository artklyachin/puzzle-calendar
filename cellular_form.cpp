#include "cellular_form.h"

CellularForm::CellularForm(const FormStrRepresent &other_shape)
    : cellular_form(convertToFormType(other_shape))
{
}

bool CellularForm::operator==(const CellularForm &other) const
{
    return cellular_form == other.cellular_form;
}

CellularForm::CellState CellularForm::get_cell(int row, int colomn) const
{
    auto [n, m] = size();
    if (row < 0 || row >= n)
        return CellState::NotIncluded;
    if (colomn < 0 || colomn >= m)
        return CellState::NotIncluded;

    return cellular_form[row][colomn] ? CellState::Included : CellState::NotIncluded;
}

FormType CellularForm::convertToFormType(const FormStrRepresent &representation) const
{
    size_t n = representation.size(), m = representation[0].size();
    FormType res(n, std::vector<int>(m, 0));
    for (int line = 0; line < n; ++line)
    {
        for (int column = 0; column < m; ++column)
        {
            res[line][column] = int(representation[line][column] != '.');
        }
    }
    return res;
}

std::pair<size_t, size_t> CellularForm::size() const
{
    return {cellular_form.size(), cellular_form[0].size()};
}
