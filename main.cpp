#include <stdio.h>
#include <vector>
#include <iostream>
#include <chrono>

#include "src/octree.hpp"
#include "src/point.hpp"

void test_octree(std::vector<Point *> insert_points, int insert_point_limit, std::vector<Point *> search_points, std::vector<int> octree_depths);

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
    std::vector<Point *> small_search_points = points;
    small_search_points.push_back(new Point(0, 0, 2.1));
    small_search_points.push_back(new Point(0, 0, 1));
    small_search_points.push_back(new Point(1, -1, 6));
    for (int i = 0; i < small_search_points.size(); i++)
    {
        std::cout << "Searching for point " << *small_search_points[i] << ": ";
        bool found = tree.find(small_search_points[i]);
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

    // Create insert points
    int insert_count = 10000000;
    std::vector<Point *> insert_points;
    std::cout << "Creating " << insert_count << " points..." << std::endl;
    for (int i = 0; i < insert_count; i++)
    {
        float rand_x = ((float)std::rand()) / (float)RAND_MAX * 100.0f;
        float rand_y = ((float)std::rand()) / (float)RAND_MAX * 100.0f;
        float rand_z = ((float)std::rand()) / (float)RAND_MAX * 100.0f;
        insert_points.push_back(new Point(rand_x, rand_y, rand_z));
    }

    // Create search points
    int search_count = 100;
    std::vector<Point *> search_points;
    std::cout << "Creating " << search_count << " search points..." << std::endl;
    for (int i = 0; i < search_count; i++)
    {
        float rand_x = ((float)std::rand()) / (float)RAND_MAX * 100.0f;
        float rand_y = ((float)std::rand()) / (float)RAND_MAX * 100.0f;
        float rand_z = ((float)std::rand()) / (float)RAND_MAX * 100.0f;
        search_points.push_back(new Point(rand_x, rand_y, rand_z));
    }

    // Test insertion and seach with different amounts of points and octree depth
    std::vector<int> depths = std::vector<int>();
    depths.push_back(0);
    depths.push_back(1);
    depths.push_back(2);
    depths.push_back(4);
    depths.push_back(6);
    std::cout << "Octree size, ";
    for (int i = 0; i < depths.size(); i++)
    {
        std::cout << "Max depth = " << depths[i] << ", ";
    }

    std::cout << std::endl;

    for (int i = 0; i <= 4000000; i += 50000)
    {
        test_octree(insert_points, i, search_points, depths);
    }

    printf("Finished testing octree!\n");
    return 0;
}

void test_octree(std::vector<Point *> insert_points, int insert_point_limit, std::vector<Point *> search_points, std::vector<int> octree_depths)
{
    clock_t start, end;
    std::cout << insert_point_limit << ", ";
    for (int d = 0; d < octree_depths.size(); d += 1)
    {
        Octree test_tree(Point(0, 0, 0), Point(100, 100, 100), octree_depths[d]);

        // start = clock();
        for (int i = 0; i < insert_point_limit; i++)
        {
            test_tree.insert(insert_points[i]);
        }
        // end = clock();
        // int duration = (int)((float)(end - start) * 1000.0f / CLOCKS_PER_SEC);

        start = clock();
        for (int i = 0; i < search_points.size(); i++)
        {
            test_tree.find_closest(search_points[i]);
        }
        end = clock();
        float duration = ((float)(end - start) * 1000.0f / CLOCKS_PER_SEC) / search_points.size();
        std::cout << duration << ", ";
    }
    std::cout << std::endl;
}
