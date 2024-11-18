#include "Point.h"
#include "TestSuite.h"

/// @brief Constructs a Point with the given x and y coordinates.
/// @param x The x coordinate.
/// @param y The y coordinate.
Point::Point(int x, int y) : x(x), y(y) {}

/// @brief Constructs a Point with both coordinates set to 0.
Point::Point() {
    x = 0;
    y = 0;
}

/// @brief Returns the x coordinate of the point.
/// @return The x coordinate.
int Point::getX() const {
    return x;
}

/// @brief Sets the x coordinate of the point.
/// @param x The x coordinate to set.
void Point::setX(int x) {
    this->x = x;
}

/// @brief Returns the y coordinate of the point.
/// @return The y coordinate.
int Point::getY() const {
    return y;
}

/// @brief Sets the y coordinate of the point.
/// @param y The y coordinate to set.
void Point::setY(int y) {
    this->y = y;
}

/// @brief Sets the x and y coordinates of the point.
/// @param x The x coordinate to set.
/// @param y The y coordinate to set.
void Point::setXY(int x, int y) {
    this->x = x;
    this->y = y;
}

/// @brief Swaps the x and y coordinates of the point.
void Point::swapXY() {
    std::swap(x, y);
}

/// @brief Multiplies the x coordinate of the point by the given factor.
/// @param factor The factor to multiply the x coordinate by.
void Point::multiplyX(int factor) {
    x *= factor;
}

/// @brief Multiplies the y coordinate of the point by the given factor.
/// @param factor The factor to multiply the y coordinate by.
void Point::multiplyY(int factor) {
    y *= factor;
}

/// @brief Returns a string representation of the point in the format "(x, y)".
/// @return A string representation of the point.
std::string Point::toString() const {
    std::stringstream ss;
    ss << "(" << x << ", " << y << ")";
    return ss.str();
}

Point Point::operator+(const Point& other) const {
    return Point(x + other.x, y + other.y);
}

bool operator==(const Point& left, const Point& right) {
    return (left.x == right.x) && (left.y == right.y);
}

std::ostream& operator<<(std::ostream& os, const Point& point) {
    os << point.toString();
    return os;
}

int main() {
    // Run tests
    TestSuite::runTestSuite();
    return 0;
}
