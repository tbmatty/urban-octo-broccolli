#pragma once

#include "game_object.hpp"
#include <SDL_ttf.h>
#include <string>

class TextGameObject : public GameObject {
public:
    TextGameObject(Vector2 position, Vector2 size, const std::string &text, TTF_Font *font, bool isActive);
    bool loadTexture(const std::string& imagePath, SDL_Renderer* renderer) override;
    void render(SDL_Renderer* renderer) override;
    std::string text;
    TTF_Font *font;
    SDL_Color color;
    bool isActive;
};