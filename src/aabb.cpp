#include "aabb.hpp"

#include <iostream>

AABB::AABB() : lower(), upper() {}

AABB::AABB(Point lower, Point upper) : lower(lower), upper(upper) {}

AABB::AABB(std::vector<Point *> points)
{
    if (points.size() == 0)
    {
        return;
    }

    float min_x, max_x, min_y, max_y, min_z, max_z;

    min_x = points[0]->x;
    max_x = points[0]->x;
    min_y = points[0]->y;
    max_y = points[0]->y;
    min_z = points[0]->z;
    max_z = points[0]->z;

    for (int i = 1; i < points.size(); i++)
    {
        Point *p = points.at(i);
        min_x = p->x < min_x ? p->x : min_x;
        max_x = p->x > max_x ? p->x : max_x;
        min_y = p->y < min_y ? p->y : min_y;
        max_y = p->y > max_y ? p->y : max_y;
        min_z = p->z < min_z ? p->z : min_z;
        max_z = p->z > max_z ? p->z : max_z;
    }

    lower = Point(min_x, min_y, min_z);
    upper = Point(max_x, max_y, max_z);
}

bool AABB::includes(Point *p)
{
    return p->x >= lower.x && p->x <= upper.x &&
           p->y >= lower.y && p->y <= upper.y &&
           p->z >= lower.z && p->z <= upper.z;
}

std::vector<AABB *> AABB::subdivide()
{
    std::vector<AABB *> divisions;
    Point halfSize = (upper - lower) / 2.0f;
    divisions.push_back(new AABB(lower, lower + halfSize));
    divisions.push_back(new AABB(lower + halfSize.x_component(), lower + halfSize + halfSize.x_component()));
    divisions.push_back(new AABB(lower + halfSize.y_component(), lower + halfSize + halfSize.y_component()));
    divisions.push_back(new AABB(lower + halfSize.x_component() + halfSize.y_component(), lower + halfSize + halfSize.x_component() + halfSize.y_component()));
    divisions.push_back(new AABB(lower + halfSize.z_component(), lower + halfSize + halfSize.z_component()));
    divisions.push_back(new AABB(lower + halfSize.x_component() + halfSize.z_component(), lower + halfSize + halfSize.x_component() + halfSize.z_component()));
    divisions.push_back(new AABB(lower + halfSize.y_component() + halfSize.z_component(), lower + halfSize + halfSize.y_component() + halfSize.z_component()));
    divisions.push_back(new AABB(lower + halfSize.x_component() + halfSize.y_component() + halfSize.z_component(), upper));
    return divisions;
}

std::ostream &operator<<(std::ostream &os, const AABB &aabb)
{
    os << "AABB " << aabb.lower << "-" << aabb.upper;
    return os;
}
