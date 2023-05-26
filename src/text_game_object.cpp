#include "text_game_object.hpp"

TextGameObject::TextGameObject(Vector2 position, Vector2 size, const std::string &text, TTF_Font *font, bool isActive)
    : GameObject(position, size, isActive), text(text), font(font){
    std::cout << "isActive in TextGameObject constructor: " << isActive << std::endl;
};

bool TextGameObject::loadTexture(const std::string& imagePath, SDL_Renderer* renderer){
    return true;
};
void TextGameObject::render(SDL_Renderer* renderer){
    // std::cout << "Initialising textSurface in TextGameObject.render(renderer)" << std::endl;
    
    // std::cout << "Font pointer: " << font << std::endl;
    // std::cout << "Text: " << text << std::endl;
    // std::cout << "Color (R, G, B, A): (" << static_cast<int>(color.r) << ", " << static_cast<int>(color.g) << ", " << static_cast<int>(color.b) << ", " << static_cast<int>(color.a) << ")" << std::endl;
    if(getIsActive())
    {
        color = SDL_Color{255, 255, 255, 255};
    } else {
        color = SDL_Color{128, 128, 128, 255};
    }


    SDL_Surface *textSurface = TTF_RenderText_Solid(font, text.c_str(), color);
    
    // std::cout << "TTF_RenderText_Solid result: " << textSurface << std::endl;

    if (!textSurface) {
        std::cerr << "TTF_RenderText_Solid: " << TTF_GetError() << std::endl;
        return;
    }
    // The rest of the method
    // std::cout << "Initialising textTexture in TextGameObject.render(renderer)" << std::endl;
    SDL_Texture *textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    SDL_FreeSurface(textSurface);

    if (!textTexture) {
        std::cerr << "SDL_CreateTextureFromSurface: " << SDL_GetError() << std::endl;
        return;
    }

    // std::cout << "Creating SDL_Rect in TextGameObject.render(renderer)" << std::endl;
    SDL_Rect rect = {static_cast<int>(position.getV1()), static_cast<int>(position.getV2()),
                     static_cast<int>(size.getV1()), static_cast<int>(size.getV2())};
    
    // std::cout << "Rendering Copy in TextGameObject.render(renderer)" << std::endl;
    SDL_RenderCopy(renderer, textTexture, nullptr, &rect);
    SDL_DestroyTexture(textTexture);
};