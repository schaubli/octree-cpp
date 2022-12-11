#include <stdio.h>
#include <vector>
#include <iostream>

#include "src/octree.hpp"
#include "src/point.hpp"


int main() {
    printf("Testing octree...\n");

    std::vector<Point> points;
    points.push_back(Point(0,0,0));
    points.push_back(Point(0,-1,1));
    points.push_back(Point(1,0,4));
    Octree tree(points);
    std::cout << tree.aabb << std::endl;
    printf("Finished testing octree!\n");
    return 0;
}
