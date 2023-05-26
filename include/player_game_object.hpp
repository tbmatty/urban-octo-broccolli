#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include "game_object.hpp"
#include <iostream>

class PlayerGameObject : public GameObject {
public:
    PlayerGameObject(Vector2 position, Vector2 size, bool isActive /*= false*/);
    bool loadTexture(const std::string& imagePath, SDL_Renderer* renderer) override;
    void render(SDL_Renderer* renderer) override;

    virtual ~PlayerGameObject(); // Declare the destructor as virtual

private:
    SDL_Texture* texture;
};

