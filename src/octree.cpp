#include "octree.hpp"

#include <iostream>

Octree::Octree() : aabb(), point(nullptr) {
}

Octree::Octree(std::vector<Point*> points) : aabb(points), point(nullptr)  {
    for(int i=0; i<points.size(); i++) {
        insert(points[i]);
    }
}


Octree::Octree(Point lower, Point upper) : aabb(lower, upper), point(nullptr)  {}


Octree::Octree(AABB aabb) : aabb(aabb) {}

bool Octree::insert(Point* p) {
    // TODO: Check if point is already in octree

    if (aabb.includes(p) == false) {
        std::cout << "Not included! ";
        return false;
    }

    if (children.size() == 0) {
        if (point == nullptr) {
            std::cout << "Initial point in " << aabb << ". ";
            point = p;
            return true;
        } else {
            // Check if point already exists
            if (*point == *p) {
                std::cout << "Point already in octree! ";
                return false;
            }
            // Subdivide            
            std::cout << "Subdividing octree. ";
            std::vector<AABB*> aabbs = aabb.subdivide();
            for(int i=0; i<aabbs.size(); i++) {
                Octree* newChild = new Octree(*aabbs[i]);
                children.push_back(newChild);
                if (newChild->aabb.includes(point)) {
                    newChild->insert(point);
                }
            }
            point = nullptr;
        }
    }

    // Find correct aabb that contains point
    for(int i=0; i<children.size(); i++) {
        if (children[i]->aabb.includes(p) == true) {
            return children[i]->insert(p);
        }
    }
    return false;
}

bool Octree::find(Point* p) {
    if (point != nullptr && *point == *p) {
        return true;
    }
    for(int i=0; i<children.size(); i++) {
        if (children[i]->aabb.includes(p) == true) {
            return children[i]->find(p);
        }
    }
    return false;
}



std::ostream& operator<<(std::ostream& os, const Octree& octree) {
    if (octree.point == nullptr) {
        os << "Octree (empty): " << octree.aabb;
    } else {
        os << "Octree (" << (*octree.point) << "): " << octree.aabb;
    }
    return os;
}
