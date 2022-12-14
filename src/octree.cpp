#include "octree.hpp"

#include <iostream>

Octree::Octree() : aabb(), points() {}

Octree::Octree(std::vector<Point *> points) : Octree(points, 4) {}

Octree::Octree(std::vector<Point *> points, int max_depth) : aabb(points), points(), max_depth(max_depth)
{
    for (int i = 0; i < points.size(); i++)
    {
        insert(points[i]);
    }
}

Octree::Octree(Point lower, Point upper) : Octree(lower, upper, 4) {}

Octree::Octree(Point lower, Point upper, int max_depth) : aabb(lower, upper), points(), max_depth(max_depth) {}

Octree::Octree(AABB aabb) : Octree(aabb, 4) {}

Octree::Octree(AABB aabb, int max_depth) : aabb(aabb), max_depth(max_depth), points(0) {}

bool Octree::insert(Point *p)
{
    if (aabb.includes(p) == false)
    {
        return false;
    }
    if (children.size() == 0)
    {
        // Check if point already exists
        // for (int i = 0; i < points.size(); i++)
        // {
        //     if (*points[i] == *p)
        //     {
        //         // std::cout << "Point already in octree! " << std::endl;
        //         return false;
        //     }
        // }
        if (points.size() == 0 || max_depth < 1)
        {
            // Reached max depth
            points.push_back(p);
            return true;
        }
        else
        {
            // Subdivide
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

bool Octree::find(Point *p) const
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

Point *Octree::find_closest(Point *p) const
{
    if (children.size() == 0)
    {
        // Search in own points
        if (points.size() == 0)
        {
            return nullptr;
        }
        float min_dist = (*p - *points[0]).length();
        Point *closest_p = points[0];
        for (int i = 1; i < points.size(); i++)
        {
            float curr_dist = (*p - *points[i]).length();
            if (curr_dist < min_dist)
            {
                min_dist = curr_dist;
                closest_p = points[i];
            }
        }
        return closest_p;
    }
    else
    {
        // Search inside first and then outside of children
        Point *closest_p = nullptr;
        if (aabb.includes(p))
        {
            for (int i = 0; i < children.size(); i++)
            {
                if (children[0]->aabb.includes(p))
                {
                    closest_p = children[0]->find_closest(p);
                    break;
                }
            }
        }

        for (int i = 0; i < children.size(); i++)
        {
            if (children[i]->aabb.includes(p) == false && (closest_p == nullptr || children[i]->aabb.distance_outside(p) < (*closest_p - *p).length()))
            {
                Point *new_closest = children[i]->find_closest(p);
                if (new_closest != nullptr && (closest_p == nullptr || (*p - *new_closest).length() < (*p - *closest_p).length()))
                {
                    closest_p = new_closest;
                }
            }
        }
        return closest_p;
    }
}

int Octree::count_aabbs() const
{
    if (children.size() == 0)
    {
        return 1;
    }
    int sum = 0;
    for (int i = 0; i < children.size(); i++)
    {
        sum += children[i]->count_aabbs();
    }
    return sum;
}

int Octree::count_filled_max_depth_aabbs() const
{
    if (children.size() == 0)
    {
        return max_depth < 1 && points.size() > 0 ? 1 : 0;
    }
    int sum = 0;
    for (int i = 0; i < children.size(); i++)
    {
        sum += children[i]->count_filled_max_depth_aabbs();
    }
    return sum;
}

Octree::~Octree() {
    for (int i = 0; i < children.size(); i++)
    {
        delete children[i];
    }
}

std::ostream &operator<<(std::ostream &os, const Octree &octree)
{
    int aabbs = octree.count_aabbs();
    int filled_aabbs = octree.count_filled_max_depth_aabbs();
    float fill_amount = filled_aabbs * 1.0f / aabbs;
    if (octree.points.size() == 0)
    {
        os << "Octree (empty): " << octree.aabb << " with " << (int)(fill_amount * 100.0f) << "\% of max depth aabbs filled";
    }
    else
    {
        os << "Octree (filled): " << octree.aabb << " with " << (int)(fill_amount * 100.0f) << "\% of max depth aabbs filled";
    }
    return os;
}
