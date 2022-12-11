#pragma once

struct Point {
    float x;
    float y;
    float z;

    // Constructors
    Point() : x(0), y(0), z(0) {};
    Point(float new_x, float new_y, float new_z) : x(new_x), y(new_y), z(new_z) {}
};
