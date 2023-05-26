#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>

class Tile {
public:
    Tile(int x, int y, int width, int height, int tileType);
    ~Tile();
    void render(SDL_Renderer *renderer);
    bool loadTexture(const std::string& imagePath, SDL_Renderer* renderer);
    bool hasTexture() const;
    void setPosition(int x, int y);
private:
    int x;
    int y;
    TTF_Font* font;
    SDL_Color color;
    std::string text;
    int width;
    int height;
    int tileType;
    SDL_Texture* texture;
};