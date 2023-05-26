#include "game_object.hpp"

GameObject::GameObject(Vector2 position, Vector2 size, bool isActive /*= false*/)
    : position(position), size(size), isActive(isActive) {   
};

Vector2& GameObject::getPosition(){return position;}
Vector2& GameObject::getSize(){return size;}
bool& GameObject::getIsActive(){return isActive;}

void GameObject::setPosition(Vector2 position){this->position = position;}
void GameObject::setSize(Vector2 size){this->size = size;}
void GameObject::setIsActive(bool isActive)
{
    std::cout << "set is active called: " << std::boolalpha << isActive << std::endl; // Output: true
    this->isActive = isActive;}
// void GameObject::transformPosition(float speed, Vector2 direction, float deltaTime)
// {
//     std::cout << "Hello" << std::endl;
//     // scale the direction vector by speed
//     direction.scaleByMagnitude(speed * deltaTime);
//     std::cout << "Goodbye" << std::endl;
//     std::cout << "this transform: " << this << std::endl;
//     // copy the direction vector
//     Vector2 directionCopy = direction;
//     // transform position with direction (just matrix addition)
//     this->position.addVector(std::move(directionCopy));
//     std::cout << "I don't know why" << std::endl;
// }

void GameObject::transformPosition(float speed, Vector2 direction, float deltaTime)
{
    std::cout << "Hello" << std::endl;

    // Adjust the direction vector for isometric movement
    float isoX = (direction.getV1() - direction.getV2()) / 2;
    float isoY = (direction.getV1() + direction.getV2()) / 2;
    direction.setV1(isoX);
    direction.setV2(isoY);

    // scale the direction vector by speed
    direction.scaleByMagnitude(speed * deltaTime);
    
    std::cout << "Goodbye" << std::endl;
    std::cout << "this transform: " << this << std::endl;

    // copy the direction vector
    Vector2 directionCopy = direction;

    // transform position with direction (just matrix addition)
    this->position.addVector(std::move(directionCopy));
    
    std::cout << "I don't know why" << std::endl;
}
