#ifndef LAB6_POINT_H
#define LAB6_POINT_H

#include <iostream>
#include <sstream>

/// @brief Represents a point on a 2D grid
class Point {
    friend class TestSuite;
    friend std::ostream& operator<<(std::ostream& os, const Point& point);
public:
    /// @brief Default constructor
    Point();

    /// @brief Constructor
    /// @param x - x coordinate
    /// @param y - y coordinate
    Point(int x, int y);

    /// @brief Returns the x value
    /// @return x coordinate
    int getX() const;

    /// @brief Returns the y value
    /// @return y coordinate
    int getY() const;

    /// @brief Sets the x value
    /// @param x - x coordinate
    void setX(int x);

    /// @brief Sets the y value
    /// @param y - y coordinate
    void setY(int y);

    /// @brief Sets the x and y values
    /// @param x - x coordinate
    /// @param y - y coordinate
    void setXY(int x, int y);

    /// @brief Swaps the x and y values
    void swapXY();

    /// @brief Multiplies the x value by a factor
    /// @param factor - factor to multiply by
    void multiplyX(int factor);

    /// @brief Multiplies the y value by a factor
    /// @param factor - factor to multiply by
    void multiplyY(int factor);

    /// @brief Returns the string representation of the point
    /// @return string representation of the point
    std::string toString() const;

    /// @brief Overloaded + operator
    /// @param other - other point to add
    /// @return new point with the sum of the x and y values
    Point operator+(const Point& other) const;

    /// @brief Overloaded == operator
    /// @param left - left point to compare
    /// @param right - right point to compare
    /// @return true if the points are equal, false otherwise
    friend bool operator==(const Point& left, const Point& right);

private:
    int x;
    int y;
};


#endif //POINT_H
