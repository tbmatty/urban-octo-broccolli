#pragma once
#include <iostream>
#include <SDL.h>

class Vector2 {
public:
    Vector2(float v1, float v2);
    ~Vector2() = default;

    float getV1() const;
    float getV2() const;

    void setV1(float v1);
    void setV2(float v2);
    void scaleByMagnitude(const float scale);
    void scaleByVector(const Vector2 &scale);
    void addVector(Vector2&& v);
protected:
    float v1;
    float v2;
};