#include "aabb.hpp"

#include <iostream>

AABB::AABB() : lower(), upper(){
}

AABB::AABB(std::vector<Point> points) {
    if (points.size() == 0) {
        return;
    }

    float min_x, max_x, min_y, max_y, min_z, max_z;

    min_x = points[0].x;
    max_x = points[0].x;
    min_y = points[0].y;
    max_y = points[0].y;
    min_z = points[0].z;
    max_z = points[0].z;

    for (int i=1; i<points.size(); i++) {
        Point p = points.at(i);
        min_x = p.x < min_x ? p.x : min_x;
        max_x = p.x > max_x ? p.x : max_x;
        min_y = p.y < min_y ? p.y : min_y;
        max_y = p.y > max_y ? p.y : max_y;
        min_z = p.z < min_z ? p.z : min_z;
        max_z = p.z > max_z ? p.z : max_z;
    }

    lower = Point(min_x, min_y, min_z);
    upper = Point(max_x, max_y, max_z);
}

std::ostream& operator<<(std::ostream& os, const AABB& aabb) {
    os << "X: " << aabb.lower.x << " to " << aabb.upper.x << " ";
    os << "Y: " << aabb.lower.y << " to " << aabb.upper.y << " ";
    os << "Z: " << aabb.lower.z << " to " << aabb.upper.z ;
    return os;
}

