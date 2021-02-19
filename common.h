#ifndef __COMMON_H
#define __COMMON_H

#include <stdlib.h>

#include <iostream>
#include <string>
using namespace std;

const int total_board_colors = 6;
const char board_colors[total_board_colors] = {'p','y','b','o','g','r'};

const int total_special_colors = 7;
const char candy_hearts = 'H',
           peppermint_forest = 'F',
           gingerbread_tree = 'N',
           gumdrop_mountains = 'D',
           peanutbrittle_house = 'T',
           lollypop_woods = 'L',
           icecream_floats = 'I';
const char special_colors[total_special_colors] = {candy_hearts, peppermint_forest, gingerbread_tree, gumdrop_mountains, peanutbrittle_house, lollypop_woods, icecream_floats};

#endif
