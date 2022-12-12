#include "octree.hpp"

#include <iostream>

Octree::Octree() : aabb(), points()
{
}

Octree::Octree(std::vector<Point *> points) : Octree(points, 6)
{
}

Octree::Octree(std::vector<Point *> points, int max_depth) : aabb(points), points(), max_depth(max_depth)
{
    for (int i = 0; i < points.size(); i++)
    {
        insert(points[i]);
    }
}

Octree::Octree(Point lower, Point upper) : Octree(lower, upper, 6) {}

Octree::Octree(Point lower, Point upper, int max_depth) : aabb(lower, upper), points(), max_depth(max_depth) {}

Octree::Octree(AABB aabb) : Octree(aabb, 6) {}
Octree::Octree(AABB aabb, int max_depth) : aabb(aabb), max_depth(max_depth), points(0) {}

bool Octree::insert(Point *p)
{
    // TODO: Check if point is already in octree

    if (aabb.includes(p) == false)
    {
        std::cout << "Not included! " << std::endl;
        return false;
    }
    if (children.size() == 0)
    {
        // Check if point already exists
        for (int i = 0; i < points.size(); i++)
        {
            if (*points[i] == *p)
            {
                std::cout << "Point already in octree! " << std::endl;
                return false;
            }
        }
        if (points.size() == 0 || max_depth < 1)
        {
            if (max_depth<1) {
                std::cout << "Reached max depth in " << aabb << ". " << std::endl;
            }
            std::cout << "Initial point in " << aabb << ". " << std::endl;
            points.push_back(p);
            return true;
        }
        else
        {
            // Subdivide
            std::cout << "Subdividing octree. " << std::endl;
            std::vector<AABB *> aabbs = aabb.subdivide();
            for (int i = 0; i < points.size(); i++)
            {
                for (int j = 0; j < aabbs.size(); j++)
                {
                    Octree *newChild = new Octree(*aabbs[j], max_depth - 1);
                    children.push_back(newChild);
                    if (newChild->aabb.includes(points[i]))
                    {
                        newChild->insert(points[i]);
                    }
                }
            }
            points.clear();
        }
    }

    // Find correct aabb that contains point
    for (int i = 0; i < children.size(); i++)
    {
        if (children[i]->aabb.includes(p) == true)
        {
            return children[i]->insert(p);
        }
    }
    return false;
}

bool Octree::find(Point *p)
{
    for (int i = 0; i < points.size(); i++)
    {
        if (*points[i] == *p)
        {
            return true;
        }
    }
    for (int i = 0; i < children.size(); i++)
    {
        if (children[i]->aabb.includes(p) == true)
        {
            return children[i]->find(p);
        }
    }
    return false;
}

std::ostream &operator<<(std::ostream &os, const Octree &octree)
{
    if (octree.points.size() == 0)
    {
        os << "Octree (empty): " << octree.aabb;
    }
    else
    {
        os << "Octree (filled): " << octree.aabb;
    }
    return os;
}
