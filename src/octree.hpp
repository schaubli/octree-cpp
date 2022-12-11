#pragma once

#include "point.hpp"
#include "aabb.hpp"
#include <vector>

class Octree {
private:
    std::vector<Octree*> children;
public:
    AABB aabb;
    Point* point = nullptr;
    Octree();
    Octree(std::vector<Point*> points);
    Octree(Point lower, Point upper);
    Octree(AABB aabb);
    bool insert(Point* p);
    bool find(Point* p);
};

std::ostream& operator<<(std::ostream& os, const Octree& octree);
