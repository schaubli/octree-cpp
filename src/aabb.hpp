#pragma once

#include "point.hpp"
#include <vector>

struct AABB {

private:

public:
    Point lower;
    Point upper;
    AABB();
    AABB(float min_x, float max_x, float min_y, float max_y, float min_z, float max_z);
    AABB(std::vector<Point*> points);
    AABB(Point lower, Point upper);

    bool includes(Point *p);
    std::vector<AABB*> subdivide();
};

std::ostream& operator<<(std::ostream& os, const AABB& aabb);
