#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>

class Tile {
public:
    Tile(int x, int y, int width, int height, int tileType, int screenX, int screenY);
    ~Tile();
    void render(SDL_Renderer *renderer);
    bool loadTexture(const std::string& imagePath, SDL_Renderer* renderer);
    bool hasTexture() const;
    void setPosition(int x, int y);
    int getX() const;
    int getY() const;
    int getType() const;
    void setScreenX(int screenX);
    void setScreenY(int screenY);
    int getScreenX() const;
    int getScreenY() const;

private:
    int x;
    int y;
    int screenX;
    int screenY;
    TTF_Font* font;
    SDL_Color color;
    std::string text;
    int width;
    int height;
    int tileType;
    SDL_Texture* texture;
};