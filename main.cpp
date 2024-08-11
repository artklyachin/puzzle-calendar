#include "iostream"
#include "puzzle.h"

int main()
{
    CalendarPuzzel puzzleSolution;
    std::cout << "Resolution may take up to 10 seconds" << std::endl;

    while (true)
    {
        int date, month;
        std::cout << "date:" << std::endl;
        std::cin >> date;
        std::cout << "month:" << std::endl;
        std::cin >> month;
        puzzleSolution.print_one_solution(date, month);
    }
}
