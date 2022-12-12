#pragma once

#include <iostream>

class Point
{

public:
    float x;
    float y;
    float z;

    // Constructors
    Point() : x(0), y(0), z(0){};
    Point(float new_x, float new_y, float new_z) : x(new_x), y(new_y), z(new_z) {}
    Point operator+(Point other);
    Point operator-(Point other);
    Point operator/(float divisor);
    bool operator==(Point other);
    float length();
    Point x_component();
    Point y_component();
    Point z_component();
};

std::ostream &operator<<(std::ostream &os, const Point &p);
