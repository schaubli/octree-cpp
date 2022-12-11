#pragma once

#include "point.hpp"
#include "aabb.hpp"
#include <vector>

class Octree {
private:
public:
    AABB aabb;
    Octree();
    Octree(std::vector<Point> points);
};
