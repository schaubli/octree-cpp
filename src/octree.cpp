#include "octree.hpp"

Octree::Octree() : aabb() {

}

Octree::Octree(std::vector<Point> points) : aabb(points) {
    
}
