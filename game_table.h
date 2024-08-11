#include <vector>
#include <map>
#include "shapes.h"
#include "cellular_form.h"

class GameTable
{
public:
        GameTable(FormStrRepresent str_repr_table, const std::map<char, FormStrRepresent> &str_repr_shapes);
        void print_solition();

private:
        bool insert_shapes_starting_from_index(int index);
        void create_all_shapes(const std::map<char, FormStrRepresent> &str_repr_shapes);

        Table table;
        std::map<char, std::vector<Shape>> shapes;
        std::vector<char> shapes_names = {'O', 'U', 'Z', 'V', 'L', 'N', 'Y', 'P'};

        std::vector<std::vector<int>> dates;

        std::vector<std::tuple<std::pair<int, int>, char, int>> shapes_answer_coordinate;
};
