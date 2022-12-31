#include "utils/geometry.h"
#include <cmath>


bool Vector2::IsZero() {
    return this->x == 0 && this->y == 0;  // TODO: compare with epsilon
}

float Vector2::CalculateLength() {
    return sqrt(this->x * this->x + this->y * this->y);
}

void Vector2::Normalize() {
    float len = this->CalculateLength();
    this->x /= len;
    this->y /= len;
}

Vector2 Vector2::FromPoints(const Point2& a, const Point2& b) {
    return Vector2(b.x - a.x, b.y - a.y);
}

void Vector2::MultiplyLength(float val) {
    this->x *= val;
    this->y *= val;
}

float Point2::DistanceBetween(const Point2& a, const Point2& b) {
    Vector2 pointsVector = Vector2::FromPoints(a, b);
    return pointsVector.CalculateLength();
}

void Point2::AddVector(const Vector2& vec) {
    this->x += vec.x;
    this->y += vec.y;
}

bool Point2::operator==(const Point2& otherPoint) {
    return fabs(this->x - otherPoint.x) < EPSILON && fabs(this->y - otherPoint.y) < EPSILON;
}
