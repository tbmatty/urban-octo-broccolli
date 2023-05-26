#include "player_game_object.hpp"

PlayerGameObject::PlayerGameObject(Vector2 position, Vector2 size, bool isActive /*= false*/)
    : GameObject(position,size,isActive) {
};

bool PlayerGameObject::loadTexture(const std::string& imagePath, SDL_Renderer* renderer)
{
    SDL_Surface* surface = IMG_Load(imagePath.c_str());
    if(surface == nullptr)
    {
        // Error loading images
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

void PlayerGameObject::render(SDL_Renderer* renderer)
{
    if(texture != nullptr) {
        SDL_Rect dstRect = {static_cast<int>(position.getV1()), static_cast<int>(position.getV2()), static_cast<int>(size.getV1()), static_cast<int>(size.getV2())};
        SDL_RenderCopy(renderer, texture, nullptr, &dstRect);
    }
}

PlayerGameObject::~PlayerGameObject()
{
    if (texture != nullptr) {
        SDL_DestroyTexture(texture);
    }
}