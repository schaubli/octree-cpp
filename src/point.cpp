#include "point.hpp"

#include <iostream>
#include <cmath>

Point Point::operator+(Point other)
{
    return Point(x + other.x, y + other.y, z + other.z);
}

Point Point::operator-(Point other)
{
    return Point(x - other.x, y - other.y, z - other.z);
}

Point Point::operator/(float divisor)
{
    return Point(x / divisor, y / divisor, z / divisor);
}

bool Point::operator==(Point other)
{
    return x == other.x && y == other.y && z == other.z;
}

float Point::length() {
    return std::sqrt(std::pow(x, 2.0f) + std::pow(y, 2.0f) + std::pow(z, 2.0f));
}

Point Point::x_component()
{
    return Point(x, 0, 0);
}
Point Point::y_component()
{
    return Point(0, y, 0);
}
Point Point::z_component()
{
    return Point(0, 0, z);
}

std::ostream &operator<<(std::ostream &os, const Point &p)
{
    os << "(" << p.x << ", " << p.y << ", " << p.z << ")";
    return os;
}
