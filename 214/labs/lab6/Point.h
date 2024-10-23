//
// Created by kiefer on 10/22/24.
//

#ifndef LAB6_POINT_H
#define LAB6_POINT_H

#include <iostream>
#include <sstream>


class Point {
    friend class TestSuite; // Giving access to TestSuite class
public:
    // Default constructor
    Point();

    // Constructor
    Point(int x, int y);

    // Returns the x and y values
    int getX() const;
    int getY() const;

    // Sets the x and y values
    void setX(int x);
    void setY(int y);
    void setXY(int x, int y);

    // Swaps the x and y values
    void swapXY();

    // Multiplies the x and y values by a factor
    void multiplyX(int factor);
    void multiplyY(int factor);

    // Return the string representation of the point
    std::string toString() const;

private:
    int x;
    int y;
};


#endif //LAB6_POINT_H
