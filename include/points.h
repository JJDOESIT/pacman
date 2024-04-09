#include <iostream>

#ifndef _POINTS_
#define _POINTS_

class Points
{
private:
    const int POINT_STRING_SIZE = 7;
    int n_points = 0;
    char points_array[8] = {'0', '0', '0', '0', '0', '0', '0', '\0'};
    std::string points_string;

public:
    void update(int n);
    void reset();
    void stringify();
    std::string get_points_string();
};

#endif