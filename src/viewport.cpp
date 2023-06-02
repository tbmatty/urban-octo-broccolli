#include "viewport.hpp"

Viewport::Viewport(float x, float y, int width, int height)
    : x(x), y(y), width(width), height(height){};
float Viewport::getX() const { return x; }
float Viewport::getY() const { return y; }
float Viewport::getHeight() const { return height; }
float Viewport::getWidth() const { return width; }
Vector2 Viewport::getBottomRight() const
{
    return Vector2(x + width, y + height);
}

Vector2 Viewport::getTopLeft() const
{
    return Vector2(x, y);
}
void Viewport::setX(float x) { this->x = x; }
void Viewport::setY(float y) { this->y = y; }
void Viewport::setHeight(float height) { this->height = height; }
void Viewport::setWidth(float width) { this->width = width; }
void Viewport::updateViewport(Vector2 direction, float speed)
{

    // Calculate the distance to move in each direction
    std::cout << "Hello" << std::endl;

    // // Adjust the direction vector for isometric movement
    float isoX = (direction.getV1() - direction.getV2()) / 2;
    float isoY = (direction.getV1() + direction.getV2()) / 2;

    // // Update the position of the Viewport
    x += isoX;
    y += isoY;

    // All we need to do is add half of the offset in each direction. For example, if we move 1 in the positive direction in (x,y) we are
    // moving 1/2 in the positive direction in (x,y) and 1/2 in the negative direction in (x,y). This is because the Viewport is rectangular but player movement is isometric.

    int newX = x + (speed * (direction.getV1() / 2));
    int newY = y + (speed * (direction.getV2() / 2));
    // Update the position of the Viewport
    if (newX < 0)
    {
        x = 0;
    }
    else if (newX > 0)
    {
        std::cout << "newX: " << newX << std::endl;
        x += speed * (direction.getV1() / 2);
    }
    if (newY < 0)
    {
        y = 0;
    }
    else if (newY > 0)
    {
        std::cout << "newY: " << newY << std::endl;
        y += speed * (direction.getV2() / 2);    
    }

    // centerOn(position);
}
void Viewport::centerOn(Vector2 position)
{
    // Calculate the distance to move in each direction
    float xDistance = position.getV1() - x;
    float yDistance = position.getV2() - y;

    // Update the position of the Viewport
    x += xDistance;
    y += yDistance;
}
void Viewport::move(float x, float y)
{
    this->x += x;
    this->y += y;
}