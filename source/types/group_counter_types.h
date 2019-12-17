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
 * group_counter_types.h
 *
 *  Created on: Dec 15, 2019
 *      Author: djsweene
 */

#ifndef MAPGROUPCOUNTING_SOURCE_TYPES_GROUP_COUNTER_TYPES_H_
#define MAPGROUPCOUNTING_SOURCE_TYPES_GROUP_COUNTER_TYPES_H_

#include <vector>
#include <climits>
#include <iostream>
#include <algorithm>
#include <functional>


typedef unsigned int grouping_t;

const grouping_t NOT_GROUPED = UINT_MAX;

struct point_t
{
    unsigned int x;
    unsigned int y;

    point_t()
    {
        x = 0;
        y = 0;
    }

    point_t(unsigned int x, unsigned int y)
    {
        this->x = x;
        this->y = y;
    }
};


template <typename T>
class Map
{
public:
    Map(){}
    virtual ~Map(){}
    void push(std::vector<T> column)
    {
        map.push_back(column);
    }

    bool get_location(point_t point, T& value_out)
    {
        if(point.x < map.size() && point.y < map[point.x].size())
        {
            value_out = map[point.x][point.y];
            return true;
        }
        else
        {
            return false;
        }
    }

    bool set_location(point_t point, T value)
    {
        if(point.x < map.size() && point.y < map[point.x].size())
        {
            map[point.x][point.y] = value;
            return true;
        }
        else
        {
            return false;
        }
    }


    auto& get_map() const
    {
        return map;
    }

    void clearMap()
    {
        map.clear();
    }

    void print_map() const
    {
        unsigned int max_depth (get_max_depth());

        for(int i = (int)max_depth - 1; i >= 0; --i)
        {
            for(auto& x: map)
            {
                if((unsigned int)i < x.size())
                {
                    std::cout<<x[i]<<", ";
                }
                else
                {
                    std::cout<<" , ";
                }
            }
            std::cout<<std::endl;
        }
    }

    unsigned int get_max_depth() const
    {
        unsigned int max(0);

        for(auto& x: map)
        {
            max = std::max(max, x.size());
        }

        return max;
    }

private:

    std::vector< std::vector< T > > map;
};



#endif /* MAPGROUPCOUNTING_SOURCE_TYPES_GROUP_COUNTER_TYPES_H_ */
