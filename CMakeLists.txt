cmake_minimum_required(VERSION 3.25)
project(CalendarPuzzle)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(CalendarPuzzle 
    main.cpp 
    puzzle.cpp 
    game_table.cpp 
    shapes.cpp
    cellular_form.cpp
)
