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
 * GroupCounter.h
 *
 *  Created on: Dec 15, 2019
 *      Author: djsweene
 */

#ifndef MAPGROUPCOUNTING_SOURCE_GROUP_COUNTER_GROUPCOUNTER_H_
#define MAPGROUPCOUNTING_SOURCE_GROUP_COUNTER_GROUPCOUNTER_H_

#include "../types/group_counter_types.h"

template <typename T>
class GroupCounter
{
public:
    GroupCounter(Map<T>& starting_map, std::function<bool(const T&, const T&)> equals):
        map(starting_map),
        number_of_groups(0),
        equals_functor(equals)
    {
        build_groups_map();
    }

    virtual ~GroupCounter (){};

    void print_groups(){groups.print_map();}

    void push(std::vector<T> column)
    {
        map.push(column);

        groups.push(std::vector<grouping_t> (column.size(), NOT_GROUPED));
    }

    bool get_north(point_t point, T& value, point_t& resulting_point)
    {
        resulting_point = point;
        resulting_point.y++;

        return map.get_location(resulting_point, value);
    }

    bool get_south(point_t point, T& value, point_t& resulting_point)
    {
        resulting_point = point;
        resulting_point.y--;

        return map.get_location(resulting_point, value);
    }

    bool get_east(point_t point, T& value, point_t& resulting_point)
    {
        resulting_point = point;
        resulting_point.x++;

        return map.get_location(resulting_point, value);
    }

    bool get_west(point_t point, T& value, point_t& resulting_point)
    {
        resulting_point = point;
        resulting_point.x--;

        return map.get_location(resulting_point, value);
    }

    void print_map()
    {
        map.print_map();
    }

    void find_groups()
    {
        T current_data;
        number_of_groups = 0;

        for(unsigned int x = 0; x < map.get_map().size(); ++x)
        {
            for(unsigned int y = 0; y < map.get_map()[x].size(); ++y)
            {
                grouping_t point_group = NOT_GROUPED;
                point_t starting_point(x, y);

                if(!map.get_location(starting_point, current_data))
                {
                    continue;
                }

                if(groups.get_location(starting_point, point_group) &&
                        point_group == NOT_GROUPED)
                {
                    number_of_groups++;
                    recursive_find_group(starting_point, number_of_groups, current_data);
                }
                else
                {
                    continue;
                }
            }
        }
    }

    void recursive_find_group(point_t starting_point, grouping_t group, const T& data)
    {
        T test_data;
        point_t test_point;
        grouping_t test_group(NOT_GROUPED);

        if(!groups.set_location(starting_point, group))
        {
            //something went wrong
            std::cout<<__FILE__<<":"<<__LINE__<<":an Error got us here."<<std::endl;
            return;
        }

        //test north
        if(get_north(starting_point, test_data, test_point))
        {
            if(equals_functor(data, test_data) &&
                    groups.get_location(test_point, test_group) &&
                    test_group == NOT_GROUPED)
            {
               recursive_find_group(test_point, group, data);
            }
        }
        //test south
        if(get_south(starting_point, test_data, test_point))
        {
            if(equals_functor(data, test_data) &&
                    groups.get_location(test_point, test_group) &&
                    test_group == NOT_GROUPED)
            {
               recursive_find_group(test_point, group, data);
            }
        }
        //test east
        if(get_east(starting_point, test_data, test_point))
        {
            if(equals_functor(data, test_data)  &&
                    groups.get_location(test_point, test_group) &&
                    test_group == NOT_GROUPED)
            {
               recursive_find_group(test_point, group, data);
            }
        }
        //test west
        if(get_west(starting_point, test_data, test_point))
        {
            if(equals_functor(data, test_data) &&
                    groups.get_location(test_point, test_group) &&
                    test_group == NOT_GROUPED)
            {
               recursive_find_group(test_point, group, data);
            }
        }
    }

private:
    Map<grouping_t> groups;
    Map<T>& map;
    unsigned int number_of_groups;
    std::function<bool(const T&, const T&)> equals_functor;

    void build_groups_map()
    {
        auto raw_map = map.get_map();

        for(auto x: raw_map)
        {
            groups.push(std::vector<grouping_t> (x.size(), NOT_GROUPED));
        }
    }
};

#endif /* MAPGROUPCOUNTING_SOURCE_GROUP_COUNTER_GROUPCOUNTER_H_ */
