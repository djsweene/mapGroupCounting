/* This program is free software: you can redistribute it and/or modify  
 * it under the terms of the GNU General Public License as published by  
 * the Free Software Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful, but 
 * WITHOUT ANY WARRANTY; without even the implied warranty of 
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU 
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License 
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */
/*
 * main.cpp
 *
 *  Created on: Dec 15, 2019
 *      Author: djsweene
 */

#include <iostream>

#include "../types/group_counter_types.h"
#include "../group_counter/GroupCounter.h"

int incremental_test(void)
{
    std::cout<<"hello world!"<<std::endl;

    Map<int> test_map;

    std::vector<int> columns;

    for(int i = 0; i < 5; ++i)
        columns.push_back(i);

    test_map.push(columns);
    test_map.print_map();
    columns.clear();
    std::cout<<"---------------------"<<std::endl;

    for(int i = 0; i < 6; ++i)
        columns.push_back(i * 2);

    test_map.push(columns);
    test_map.print_map();
    columns.clear();
    std::cout<<"---------------------"<<std::endl;

    for(int i = 0; i < 4; ++i)
        columns.push_back(i * 2);

    test_map.push(columns);
    test_map.print_map();
    columns.clear();
    std::cout<<"---------------------"<<std::endl;

    GroupCounter<int> counter(test_map, [] (const int lhs, const int rhs) {return lhs == rhs;});
    point_t point(1, 3);
    point_t new_point;
    int value;

    counter.print_map();
    std::cout<<"---------------------"<<std::endl;

    test_map.get_location(point, value);
    std::cout<<"point = "<<value<<std::endl;

    counter.get_north(point, value, new_point);
    std::cout<<"north = "<<value<<std::endl;

    counter.get_south(point, value, new_point);
    std::cout<<"south = "<<value<<std::endl;

    counter.get_east(point, value, new_point);
    std::cout<<"east = "<<value<<std::endl;

    counter.get_west(point, value, new_point);
    std::cout<<"west = "<<value<<std::endl;

    std::cout<<"---------------------"<<std::endl;
    counter.print_map();
    std::cout<<"---------------------"<<std::endl;
    counter.print_groups();
    std::cout<<"---------------------"<<std::endl;
    counter.find_groups();
    std::cout<<"---------------------"<<std::endl;
    counter.print_groups();
    std::cout<<"---------------------"<<std::endl;

    std::cout<<"Cleared Map:"<<std::endl;
    test_map.clearMap();
    test_map.print_map();

    std::cout<<"Exit Success!"<<std::endl;

    return EXIT_SUCCESS;
}

int main (void)
{
    int c1[] = { 0, 10, 10,  3,  2,  5,  6};
    int c2[] = { 0,  1, 10,  3,  4,  6,  8};
    int c3[] = { 0,  1, 10, 10,  4,  7,  8,  8};
    int c4[] = { 0, 10, 10,  3,  3,  3,  8,  2};
    int c5[] = { 0, 10, 10,  3,  4,  10, 3};

    Map<int> map;

    map.push(std::vector<int>(c1, c1 + 7));
    map.push(std::vector<int>(c2, c2 + 7));
    map.push(std::vector<int>(c3, c3 + 8));
    map.push(std::vector<int>(c4, c4 + 8));
    map.push(std::vector<int>(c5, c5 + 7));

    std::cout<<"Map:"<<std::endl;
    map.print_map();

    GroupCounter<int> counter(map, [] (const int lhs, const int rhs) {return lhs == rhs;});
    std::cout<<"Groups before processing:"<<std::endl;
    counter.print_groups();

    std::cout<<"Groups after processing:"<<std::endl;
    counter.find_groups();
    counter.print_groups();

    std::cout<<"Exit Success!"<<std::endl;
    return EXIT_SUCCESS;
}


