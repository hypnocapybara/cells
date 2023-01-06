#include <cmath>
#include "utils/generic.h"


float RandomFloat(float a, float b) {
    float random = ((float) rand()) / (float) RAND_MAX;
    float diff = b - a;
    float r = random * diff;
    return a + r;
}

int RandomInt(int a, int b) {
    int diff = b - a;
    return a + (rand() % diff);
}