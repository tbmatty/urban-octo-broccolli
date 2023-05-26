#include "utilities.hpp"


bool initSDL(SDL_Window *&window, SDL_Renderer *&renderer, const char *title, int width, int height)
{

    std::cout << "Initialising SDL." << std::endl;
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        std::cerr << "Error initialising SDL: " << SDL_GetError() << std::endl;
        return false;
    }

    std::cout << "Initialising TTF." << std::endl;
    if (TTF_Init() == -1)
    {
        std::cerr << "TTF_Init: " << TTF_GetError() << std::endl;
        ;
        return false;
    }

    std::cout << "Creating window." << std::endl;
    window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    if (!window)
    {
        std::cerr << "Error creating window: " << SDL_GetError() << std::endl;
        return false;
    }

    std::cout << "Creating renderer." << std::endl;
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer)
    {
        std::cerr << "Error creating renderer: " << SDL_GetError() << std::endl;
        return false;
    }

    return true;
}

SDL_Texture *renderText(SDL_Renderer *renderer, TTF_Font *font, const std::string &text, SDL_Color textColor)
{
    std::cout << "Beginning renderText function" << std::endl;
    SDL_Surface *textSurface = TTF_RenderText_Solid(font, text.c_str(), textColor);
    if (!textSurface)
    {
        std::cerr << "TTF_RenderText_Solid: " << TTF_GetError() << std::endl;
        return nullptr;
    }
    std::cout << "Creating texture from surface" << std::endl;
    SDL_Texture *textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    SDL_FreeSurface(textSurface);

    return textTexture;
}

void renderTextGameObject(SDL_Renderer *renderer, TextGameObject &textObject)
{
    std::cout << "renderTextGameObject" << std::endl;
    SDL_Color textColor = textObject.color;
    SDL_Texture *textTexture = renderText(renderer, textObject.font, textObject.text, textColor);
    SDL_Rect rect = {static_cast<int>(textObject.getPosition().getV1()), static_cast<int>(textObject.getPosition().getV2()), static_cast<int>(textObject.getSize().getV1()), static_cast<int>(textObject.getSize().getV2())};
    SDL_RenderCopy(renderer, textTexture, nullptr, &rect);
    SDL_DestroyTexture(textTexture);
}

void renderGameObject(SDL_Renderer *renderer, GameObject &object)
{
    // Check if the game object is a TextGameObject
    // TextGameObject *textObject = dynamic_cast<TextGameObject *>(&object);
    // if (textObject)
    // {
    //     // Render the text
    //     renderTextGameObject(renderer, *textObject);
    //     return;
    // }
    // PlayerGameObject *playerObject = dynamic_cast<PlayerGameObject *>(&object);
    // if(playerObject)
    // {
    //     //Render the playerobject
    //     playerObject->render(renderer);
    // }
    object.render(renderer);
}

void transformGameObjects(std::vector<std::unique_ptr<GameObject>>& gameObjects, const Vector2 scale)
{
    for (const auto &object : gameObjects)
    {
        object->getPosition().scaleByVector(scale);
        object->getSize().scaleByVector(scale);
    }
}


// int loadGameObjectsForState(GameState state, std::vector<std::unique_ptr<GameObject>>& gameObjects, SDL_Renderer* renderer, TTF_Font* font)
// {
//     std::cout << "Loading game objects for state" << std::endl;

//     gameObjects.clear();

//     switch(state)
//     {
//         case GameState::MainMenu:
//         {
//             //Load game objects for the main menu
//             //Create the game objects outside the main loop
//             gameObjects.push_back(std::make_unique<TextGameObject>(Vector2(150, 500), Vector2(100, 80), "Start", font, SDL_Color{255, 255, 255, 255}));
//             gameObjects.push_back(std::make_unique<TextGameObject>(Vector2(350, 500), Vector2(100, 80), "Options", font, SDL_Color{128, 128, 128, 255}));
//             gameObjects.push_back(std::make_unique<TextGameObject>(Vector2(550, 500), Vector2(100, 80), "Chapters", font, SDL_Color{128, 128, 128, 255}));
//             return 0;
//             break;
//         }
//         case GameState::Playing:
//         {
//             //Load game objects for the playing state
//             auto player = std::make_unique<PlayerGameObject>(Vector2(100,100),Vector2(64,64), false);
//             if(!player->loadTexture("C:/Users/theba/Documents/2dgameengine/cowboy1.png", renderer))
//             {
//                 //Error loading texture 
//                 return 1;
//             }
//             gameObjects.push_back(std::move(player));
//             return 0;
//             break;
//         }
//         case GameState::Paused:
//             //Load 
//             return 0;
//             break;
//     }
//     return 0;
// }