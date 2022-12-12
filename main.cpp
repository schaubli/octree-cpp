#include <stdio.h>
#include <vector>
#include <iostream>

#include "src/octree.hpp"
#include "src/point.hpp"

int main()
{
    printf("Testing octree...\n");

    Octree tree(Point(0, 0, 0), Point(10, 10, 10), 6);
    std::cout << tree << std::endl;

    // Add some points
    std::vector<Point *> points;
    points.push_back(new Point(0, 0, 2));
    points.push_back(new Point(0, -1, 1));
    points.push_back(new Point(1, 0, 4));
    points.push_back(new Point(1, 0, 4.5));
    points.push_back(new Point(2, 3, 4.5));
    points.push_back(new Point(1, 0, 6));
    points.push_back(new Point(1, 1, 9));
    points.push_back(new Point(1, 0, 4.5));
    for (int i = 0; i < points.size(); i++)
    {
        std::cout << "Inserting point " << *points[i] << ": ";
        bool inserted = tree.insert(points[i]);
        std::cout << (inserted ? "-> Point added" : "-> Point not added") << std::endl;
    }

    // Search for some points
    std::vector<Point *> search_point = points;
    search_point.push_back(new Point(0, 0, 2.1));
    search_point.push_back(new Point(0, 0, 1));
    search_point.push_back(new Point(1, -1, 6));
    for (int i = 0; i < search_point.size(); i++)
    {
        std::cout << "Searching for point " << *search_point[i] << ": ";
        bool found = tree.find(search_point[i]);
        std::cout << (found ? "found" : "not found") << std::endl;
    }

    std::vector<Point *> nearest_search_point;
    nearest_search_point.push_back(new Point(0, 0, 2.1));
    nearest_search_point.push_back(new Point(0.1, 0.1, 2.1));
    nearest_search_point.push_back(new Point(5, 5, 5));
    nearest_search_point.push_back(new Point(10, 11, 10));
    nearest_search_point.push_back(new Point(0, 0, -1));
    for (int i = 0; i < nearest_search_point.size(); i++)
    {
        std::cout << "Searching for point closest to " << *nearest_search_point[i] << ": ";
        Point *closest = tree.find_closest(nearest_search_point[i]);        
        std::cout << *closest << " with distance: " << (*nearest_search_point[i] - *closest).length() << std::endl;
    }



    printf("Finished testing octree!\n");
    return 0;
}
