cmake_minimum_required (VERSION 2.6)
project (CM)

add_executable(monty_comp monty_carlo_comp.cpp my_num.cpp)
add_executable(comp_list make_list_comp.cpp my_num.cpp)
add_executable(monty monty_carlo.cpp )
add_executable(make_list make_list.cpp)
