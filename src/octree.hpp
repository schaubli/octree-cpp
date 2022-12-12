#pragma once

#include "point.hpp"
#include "aabb.hpp"
#include <vector>

class Octree
{
private:
    std::vector<Octree *> children;
    int max_depth;

public:
    AABB aabb;
    std::vector<Point *> points;

    Octree();
    Octree(std::vector<Point *> points);
    Octree(std::vector<Point *> points, int max_depth);
    Octree(Point lower, Point upper);
    Octree(Point lower, Point upper, int max_depth);
    Octree(AABB aabb);
    Octree(AABB aabb, int max_depth);
    bool insert(Point *p);
    bool find(Point *p) const;
    Point *find_closest(Point *p) const;
    int count_aabbs() const;
    int count_filled_max_depth_aabbs() const;
};

std::ostream &operator<<(std::ostream &os, const Octree &octree);
