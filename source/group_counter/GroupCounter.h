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
    GroupCounter(Map<T>& starting_map):
        map(starting_map),
        number_of_groups(0)
    {
    }
    virtual ~GroupCounter (){};

    void print_groups(){groups.print_map();}

    bool get_north(point_t point, T& value)
    {
        point_t northern_point = point;
        northern_point.y++;

        return map.get_location(northern_point, value);
    }

    bool get_south(point_t point, T& value)
    {
        point_t southern_point = point;
        southern_point.y--;

        return map.get_location(southern_point, value);
    }

    bool get_east(point_t point, T& value)
    {
        point_t eastern_point = point;
        eastern_point.x++;

        return map.get_location(eastern_point, value);
    }

    bool get_west(point_t point, T& value)
    {
        point_t western_point = point;
        western_point.x--;

        return map.get_location(western_point, value);
    }

    void print_map()
    {
        map.print_map();
    }

private:
    Map<grouping_t> groups;
    Map<T>& map;
    unsigned int number_of_groups;

    void build_groups_map()
    {
        auto raw_map = map.getMap();

        for(auto x: raw_map)
        {
            std::vector<grouping_t> column(NOT_GROUPED, x.size());
            groups.push(column);
        }
    }
};

#endif /* MAPGROUPCOUNTING_SOURCE_GROUP_COUNTER_GROUPCOUNTER_H_ */
