#include "vector2.hpp"

Vector2::Vector2(float v1, float v2)
    :   v1(v1), v2(v2)
    {};

float Vector2::getV1() const {return v1;}
float Vector2::getV2() const {return v2;}
void Vector2::setV1(float v1){this->v1 = v1;}
void Vector2::setV2(float v2){this->v2 = v2;}
void Vector2::scaleByMagnitude(const float scale)
{
    this->v1 *= scale;
    this->v2 *= scale;
}
void Vector2::scaleByVector(const Vector2 &scale)
{
    this->v1 *= scale.getV1();
    this->v2 *= scale.getV2();
}
void Vector2::addVector(Vector2&& v)
{
    std::cout << "adding vector" << std::endl;
    std::cout << "this: " << this << std::endl;
    std::cout << "this->v1: " << this->v1 << ", this->v2: " << this->v2 << std::endl;
    std::cout << "v.v1: " << v.getV1() << ", v.v2: " << v.getV2() << std::endl;

    this->v1 += v.getV1();
    this->v2 += v.getV2();
    std::cout << "Vector added" << std::endl;
}