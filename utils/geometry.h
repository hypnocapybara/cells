#ifndef __POINT_H_CLASS__
#define __POINT_H_CLASS__


struct Point2 {
    Point2() {
        this->x = this->y = 0;
    };

    Point2(int x, int y) {
        this->x = x;
        this->y = y;
    }

    static float DistanceBetween(Point2 a, Point2 b);

    float x = 0, y = 0;
};

struct Vector2 {
    float x = 0, y = 0;
};


#endif
