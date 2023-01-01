#ifndef __POINT_H_CLASS__
#define __POINT_H_CLASS__


struct Vector2;

#define EPSILON 0.0001


struct Point2 {
    float x = 0.0f, y = 0.0f;

    Point2() {
        this->x = this->y = 0.0f;
    };

    Point2(float x, float y) {
        this->x = x;
        this->y = y;
    }

    static float DistanceBetween(const Point2& a, const Point2& b);
    static Point2 RandomPointWithinRadius(const Point2& a, float radius);
    static bool IsPointWithinRect(const Point2& a, const Point2& rectCorner, int width, int height);

    bool operator==(const Point2& otherPoint);
    Point2 operator-(const Vector2& vec);
    Point2 operator+(const Vector2& vec);
    Point2& operator+=(const Vector2& vec);
};

struct Vector2 {
    float x = 0.0f, y = 0.0f;

    Vector2() {
        this->x = this->y = 0.0f;
    };

    Vector2(float x, float y) {
        this->x = x;
        this->y = y;
    }

    bool IsZero();
    void Normalize();
    float CalculateLength();

    Vector2& operator*=(float len);
    Vector2 operator*(float len);
    Vector2& operator+=(const Vector2& vec);

    static Vector2 RandomUnitVector();
    static Vector2 FromPoints(const Point2& a, const Point2& b);
    
};


#endif
