#include <iostream>

using namespace std;
const uint8_t SATELLITE_COUNT = 24;
const uint8_t REGISTER_PAIRS[24][2] = {
    {2, 6}, 
    {3, 7},
    {4, 8},
    {5, 9},
    {1, 9},
    {2, 10},
    {1, 8},
    {2, 9},
    {3, 10},
    {2, 3},
    {3, 4},
    {5, 6},
    {6, 7},
    {7, 8},
    {8, 9},
    {9, 10},
    {1, 4},
    {2, 5},
    {3, 6},
    {4, 7},
    {5, 8},
    {6, 9},
    {1, 3},
    {4, 6}};