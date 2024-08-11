#pragma once

#include <vector>

using FormType = std::vector<std::vector<int>>;
using FormStrRepresent = std::vector<std::string>;

class CellularForm
{
public:
    CellularForm(const FormStrRepresent &other_shape);

    virtual ~CellularForm() = default;

    bool operator==(const CellularForm &other) const;

    enum class CellState
    {
        Included,
        NotIncluded
    };

    CellState get_cell(int row, int colomn) const;
    std::pair<size_t, size_t> size() const;

protected:
    FormType cellular_form;

private:
    FormType convertToFormType(const FormStrRepresent &other_shape) const;
};
