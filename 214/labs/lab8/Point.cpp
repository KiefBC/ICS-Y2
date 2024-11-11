//
// Created by kiefer on 10/22/24.
//

#include "Point.h"

Point::Point(int x, int y) : x(x), y(y) {}

Point::Point() {
    x = 0;
    y = 0;
}

int Point::getX() const {
    return x;
}

void Point::setX(int x) {
    this->x = x;
}

int Point::getY() const {
    return y;
}

void Point::setY(int y) {
    this->y = y;
}

void Point::setXY(int x, int y) {
    this->x = x;
    this->y = y;
}

void Point::swapXY() {
    std::swap(x, y);
}

void Point::multiplyX(int factor) {
    x *= factor;
}

void Point::multiplyY(int factor) {
    y *= factor;
}

std::string Point::toString() const {
    std::stringstream ss;
    ss << "(" << x << ", " << y << ")";
    return ss.str();
}
