#ifndef LAB6_POINT_H
#define LAB6_POINT_H

#include <iostream>
#include <sstream>


class Point {
    friend class TestSuite; // Giving access to TestSuite class
    friend std::ostream& operator<<(std::ostream& os, const Point& point); // Giving access to operator<< function
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

    // Overloaded operators
    Point operator+(const Point& other) const;

    friend bool operator==(const Point& left, const Point& right);

private:
    int x;
    int y;
};


#endif //POINT_H
