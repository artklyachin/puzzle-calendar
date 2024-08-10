#include "iostream"
#include <iostream>
#include <map>
#include <vector>
#include <string>

using ShapeType = std::vector<std::vector<int>>;

class CalendarPuzzel {
public:
    CalendarPuzzel();
    void print_one_solution(int date, int month);


private:

    class Game {
    public:
        Game(int date, int month, const CalendarPuzzel* curr_calendar);
        bool find_solition();
        bool has_solution_found();
        void print_solition();

    private:
        void add_date_to_calendar(int date, int month);
        bool insert_shapes_starting_from_ith(int i);
        bool check_shape_compatibility(int upper_limit, int left_border, const ShapeType& shape);
        bool display_by_template(int upper_limit, int left_border, const ShapeType& shape, int value);

        ShapeType game_table;
        bool solution_has_found;
        const CalendarPuzzel* curr_calendar;
        std::vector<std::pair<std::pair<int, int>, std::pair<int, const ShapeType&>>> ans;
    };

    std::vector<std::vector<int>> convertToShapeType(std::vector<std::string> &shape);
    static ShapeType rotate(ShapeType &shape, int count_rot90, int flipped);
    friend void test_rotate();
    void create_all_shapes();
    void create_table();

    std::map<char, std::vector<ShapeType>> shapes;
    std::vector<char> shapes_names;
    ShapeType table;
    std::map<char, std::vector<std::string>> str_repr_shapes = {
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

    std::vector<std::string> str_repr_table = {
            "......x",
            "......x",
            ".......",
            ".......",
            ".......",
            ".......",
            "...xxxx",
    };
};


void test_rotate() {
    ShapeType shape = {{0, 1, 2},
                            {3, 4, 5}};
    ShapeType res = CalendarPuzzel::rotate(shape, 0, 0);
    for (auto& line : res) {
        for (auto& elem : line) {
            std::cout << elem << " ";
        }
        std::cout << std::endl;
    }
}

std::vector<std::vector<int>> CalendarPuzzel::convertToShapeType(std::vector<std::string>& shape) {
    size_t n = shape.size(), m = shape[0].size();
    ShapeType res(n, std::vector<int>(m, 0));
    for (int line = 0; line < n; ++line) {
        for (int column = 0; column < m; ++column) {
            res[line][column] = int(shape[line][column] != '.');
        }
    }
    return res;
}

ShapeType CalendarPuzzel::rotate(ShapeType& shape, int count_rot90, int flipped) {
    size_t n = shape.size(), m = shape[0].size();
    size_t new_n = n, new_m = m;
    if (count_rot90 % 2) {
        std::swap(new_n, new_m);
    }
    if (flipped) {
        std::swap(new_n, new_m);
    }
    ShapeType rot_shape = std::vector(new_n, std::vector<int> (new_m, 0));

    for (int line = 0; line < n; ++line) {
        for (int column = 0; column < m; ++column) {
            int i = line, j = column;
            if (count_rot90 == 0) {
                if (flipped) rot_shape[j][i] = shape[line][column];
                else rot_shape[i][j] = shape[line][column];
            } else if (count_rot90 == 1) {
                if (flipped) rot_shape[n-1-i][j] = shape[line][column];
                else rot_shape[j][n-1-i] = shape[line][column];
            } else if (count_rot90 == 2) {
                if (flipped) rot_shape[m-1-j][n-1-i] = shape[line][column];
                else rot_shape[n-1-i][m-1-j] = shape[line][column];
            } else if (count_rot90 == 3) {
                if (flipped) rot_shape[i][m-1-j] = shape[line][column];
                else rot_shape[m-1-j][i] = shape[line][column];
            }
        }
    }
    return rot_shape;
}

void CalendarPuzzel::create_all_shapes() {
    for (auto& [name, elem] : str_repr_shapes) {
        ShapeType shape = convertToShapeType(elem);
        shapes_names.push_back(name);

        shapes[name] = std::vector<ShapeType>();

        //VPZLNOYU

        int rotate_count = 4;
        if (name == 'Z' || name == 'O') {
            rotate_count = 2;
        }
        for (int i = 0; i < rotate_count; ++i) {
            shapes[name].push_back(rotate(shape, i, 0));
        }

        int rotate_flipped_count = 4;
        if (name == 'Z') {
            rotate_flipped_count = 2;
        } else if (name == 'O' || name == 'V' || name == 'U') {
            rotate_flipped_count = 0;
        }
        for (int i = 0; i < rotate_flipped_count; ++i) {
            shapes[name].push_back(rotate(shape, i, 1));
        }
    }
}

void CalendarPuzzel::create_table() {
    table = convertToShapeType(str_repr_table);
}

CalendarPuzzel::CalendarPuzzel()
{
    create_table();
    create_all_shapes();
}

bool CalendarPuzzel::Game::check_shape_compatibility(int upper_limit, int left_border, const ShapeType& shape) {
    size_t shape_n = shape.size(), shape_m = shape[0].size();
    size_t table_n = game_table.size(), table_m = game_table[0].size();

    if (!(upper_limit >= 0 && upper_limit + shape_n <= table_n && left_border >= 0 && left_border + shape_m <= table_m)) return false;

    for (int line = 0; line < shape_n; ++line) {
        for (int column = 0; column < shape_m; ++column) {
            if (shape[line][column] && game_table[upper_limit + line][left_border + column]) {
                return false;
            }
        }
    }
    return true;
}

bool CalendarPuzzel::Game::display_by_template(int upper_limit, int left_border, const ShapeType& shape, int value) {
    size_t shape_n = shape.size(), shape_m = shape[0].size();
    size_t table_n = game_table.size(), table_m = game_table[0].size();

    if (!(upper_limit >= 0 && upper_limit + shape_n <= table_n && left_border >= 0 && left_border + shape_m <= table_m)) return false;

    for (int line = 0; line < shape_n; ++line) {
        for (int column = 0; column < shape_m; ++column) {
            if (shape[line][column]) {
                game_table[upper_limit + line][left_border + column] = value;
            }
        }
    }
    return true;
}


bool CalendarPuzzel::Game::insert_shapes_starting_from_ith(int shape_num) {
    if (shape_num == (*curr_calendar).shapes_names.size()) return true;

    size_t n = game_table.size(), m = game_table[0].size();
    char name = (*curr_calendar).shapes_names[shape_num];

    for (auto& shape : (*curr_calendar).shapes.at(name)) {
        for (int line = 0; line < n; ++line) {
            for (int column = 0; column < m; ++column) {
                if (shape_num == 0) {
                    std::cout << shape_num << " " << line << " " << column << std::endl;
                }
                if (check_shape_compatibility(line, column, shape)) {

                    ans.push_back({{line, column}, {name, shape}}); // insert shape
                    display_by_template(line, column, shape, 1);

                    if (insert_shapes_starting_from_ith(shape_num + 1)) {
                        return true;
                    }

                    ans.pop_back(); // delete shape
                    display_by_template(line, column, shape, 0);
                }
            }
        }
    }
    return false;
}

void CalendarPuzzel::Game::add_date_to_calendar(int date, int month) {
    --date;
    --month;
    game_table[month / 6][month % 6] = 1;
    game_table[date / 7 + 2][date % 7] = 1;
}

bool CalendarPuzzel::Game::find_solition() {
    return insert_shapes_starting_from_ith(0);
}

CalendarPuzzel::Game::Game(int date, int month, const CalendarPuzzel* curr_calendar)
    : game_table((*curr_calendar).table), curr_calendar(curr_calendar)
{
    add_date_to_calendar(date, month);
    solution_has_found = find_solition();
}

bool CalendarPuzzel::Game::has_solution_found() {
    return solution_has_found;
}

void CalendarPuzzel::Game::print_solition() {
    if (!solution_has_found) {
        std::cout << "solution has not found." << std::endl;
        return;
    }

    size_t table_n = game_table.size(), table_m = game_table[0].size();
    std::vector<std::vector<char>> ans_table(table_n, std::vector<char>(table_m, '.'));

    for (auto& [bound, shape_pair] : ans) {
        auto [upper_bound, left_bound] = bound;
        auto& [shape_name, shape] = shape_pair;
        int shape_n = shape.size(), shape_m = shape[0].size();

        for (int line = 0; line < shape_n; ++line) {
            for (int column = 0; column < shape_m; ++column) {
                if (shape[line][column]) {
                    ans_table[upper_bound + line][left_bound + column] = shape_name;
                }
            }
        }
    }

    for (int line = 0; line < table_n; ++line) {
        for (int column = 0; column < table_m; ++column) {
            std::cout << ans_table[line][column] << " ";
        }
        std::cout << std::endl;
    }
}

void CalendarPuzzel::print_one_solution(int date, int month) {
    if (!(date >= 1 && date <= 31 && month >= 1 && month <= 12)) {
        std::cout << "error: incorrect date/month" << std::endl;
        return;
    }
    Game game(date, month, this);
    if (game.has_solution_found()) {
        game.print_solition();
    } else {
        std::cout << "result: no solution found" << std::endl;
    }
}


int main() {
    int date, month;
    std::cout << "date:" << std::endl;
    std::cin >> date;
    std::cout << "month:" << std::endl;
    std::cin >> month;
    CalendarPuzzel puzzleSolution;
    puzzleSolution.print_one_solution(date, month);
}

