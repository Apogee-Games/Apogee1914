#pragma once

struct Point {
    int x;
    int y;

    Point() {}
    Point(int x, int y) : x(x), y(y) {}


    friend bool operator==(const Point& p1, const Point& p2);

    friend bool operator<(const Point& p1, const Point& p2);

    friend Point operator+(const Point& p1, const Point& p2);

    friend Point operator-(const Point& p1, const Point& p2);
};
