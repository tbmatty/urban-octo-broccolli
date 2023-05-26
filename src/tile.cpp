#include "tile.hpp"

Tile::Tile(int x, int y, int width, int height, int tileType)
    : x(x), y(y), width(width), height(height), tileType(tileType), texture(nullptr){};


Tile::~Tile() {
    if(texture != nullptr) {
        SDL_DestroyTexture(texture);
        texture = nullptr;
    }
}

bool Tile::loadTexture(const std::string& imagePath, SDL_Renderer* renderer)
{
    SDL_Surface* surface = IMG_Load(imagePath.c_str());
    if(surface == nullptr)
    {
        // Error loading image
        return false;
    }

    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    if(texture == nullptr)
    {
        return false;
    }
    return true;
}

void Tile::render(SDL_Renderer* renderer)
{
    if(texture != nullptr) {
        SDL_Rect dstRect = {x, y, width, height};
        SDL_RenderCopy(renderer, texture, nullptr, &dstRect);
    }
}

bool Tile::hasTexture() const
{
    return texture != nullptr;
}

void Tile::setPosition(int x, int y)
{
    this->x = x;
    this->y = y;
}