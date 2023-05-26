#pragma once
#include "vector2.hpp"

class Viewport {
public:
    Viewport(float x, float y, int width, int height);

    float getX() const;
    float getY() const;
    float getWidth() const;
    float getHeight() const;

    Vector2 getTopLeft() const;
    Vector2 getBottomRight() const;


    void setX(float x);
    void setY(float y);
    void setWidth(float width);
    void setHeight(float height);

    void updateViewport(Vector2 position);
    void centerOn(Vector2 position);


private:
    float x;
    float y;
    int height;
    int width;
};