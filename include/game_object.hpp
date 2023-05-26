#pragma once
#include <iostream>
#include <vector2.hpp>
#include <SDL.h>
#include <memory>

class GameObject {
public:
    GameObject(Vector2 position, Vector2 size, bool isActive /*= false*/);
    virtual ~GameObject() = default;

    virtual bool loadTexture(const std::string& imagePath, SDL_Renderer* renderer) = 0;
    virtual void render(SDL_Renderer* renderer) = 0;
    // virtual void transformLocation(int scale, char axis, )
    Vector2& getPosition();
    Vector2& getSize();
    bool& getIsActive();
    void setPosition(Vector2 position);
    void setSize(Vector2 size);
    void setIsActive(bool isActive);
    
    void transformPosition(float speed,Vector2 direction, float deltaTime);
protected:
    Vector2 position;
    Vector2 size;
    bool isActive;
};
