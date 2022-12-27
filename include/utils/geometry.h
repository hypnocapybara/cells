#ifndef __POINT_H_CLASS__
#define __POINT_H_CLASS__


struct Vector2;


struct Point2 {
    float x = 0, y = 0;

    Point2() {
        this->x = this->y = 0;
    };

    Point2(int x, int y) {
        this->x = x;
        this->y = y;
    }

    static float DistanceBetween(const Point2& a, const Point2& b);

    void AddVector(const Vector2& vec);
};

struct Vector2 {
    float x = 0, y = 0;

    Vector2() {
        this->x = this->y = 0;
    };

    Vector2(int x, int y) {
        this->x = x;
        this->y = y;
    }

    bool IsZero();
    void Normalize();
    void MultiplyLength(float val);
    float CalculateLength();

    static Vector2 FromPoints(const Point2& a, const Point2& b);
    
};


#endif
