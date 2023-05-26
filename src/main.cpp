#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>
#include <vector>
#include <memory>
#include "game_object.hpp"
#include "text_game_object.hpp"
#include "player_game_object.hpp"
#include "utilities.hpp"
#include "game_manager.hpp"
#include "GameState.hpp"

// std::vector<std::unique_ptr<GameObject>> gameObjects;
// GameState currentState = GameState::MainMenu;

int main(int argc, char *argv[])
{
    // std::cout << "Beginning main" << std::endl;

    // SDL_Window *window = nullptr;
    // SDL_Renderer *renderer = nullptr;

    // int currentWidth = 800;
    // int currentHeight = 600;
    // if (!initSDL(window, renderer, "My 2D Game Engine", currentWidth, currentHeight))
    // {
    //     std::cerr << "Something wrong with initSDL" << std::endl;
    //     return 1;
    // }
    // TTF_Font *font = nullptr;
    // std::cout << "Loading font in main" << std::endl;
    // font = TTF_OpenFont("Lora-Regular.ttf", 18);
    // if (!font)
    // {
    //     std::cerr << "TTF_OpenFont: " << TTF_GetError() << std::endl;
    //     return 1;
    // }

    // SDL_Event event;
    // bool quit = false;

    // // for the main menu
    // int currentSelection = 0;
    // bool optionSelected = false;
    // loadGameObjectsForState(currentState, gameObjects, renderer, font);
    // // Main game loop
    // while (!quit)
    // {

    //     // Clear the screen
    //     SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    //     SDL_RenderClear(renderer);

    //     // Render your game objects here

    //     switch (currentState)
    //     {
    //     case GameState::MainMenu:
    //     {
    //         // Handle main menu logic and input
    //         // ...

    //         // Poll events
    //         while (SDL_PollEvent(&event))
    //         {
    //             switch (event.type)
    //             {
    //             case SDL_QUIT:
    //             {
    //                 quit = true;
    //                 break;
    //             }
    //             case SDL_WINDOWEVENT:
    //             {
    //                 switch (event.window.event)
    //                 {
    //                 case SDL_WINDOWEVENT_RESIZED:
    //                 {
    //                     // Get new window dimensions
    //                     int newWidth = event.window.data1;
    //                     int newHeight = event.window.data2;

    //                     // Calculate scaling factors
    //                     float scaleWidth = static_cast<float>(newWidth) / currentWidth;
    //                     float scaleHeight = static_cast<float>(newHeight) / currentHeight;

    //                     // Update the current window size
    //                     currentWidth = newWidth;
    //                     currentHeight = newHeight;

    //                     // Apply the transformation matrix to game objects
    //                     transformGameObjects(gameObjects, Vector2(scaleWidth, scaleHeight));

    //                     // Update the window size
    //                     SDL_SetWindowSize(window, newWidth, newHeight);
    //                     break;
    //                 }
    //                 }
    //                 break;
    //             }
    //             case SDL_KEYDOWN:
    //             {
    //                 switch (event.key.keysym.sym)
    //                 {
    //                 case SDLK_UP:
    //                 {
    //                     // Handle up arrow key input
    //                     if (currentSelection < 2)
    //                     {
    //                         currentSelection++;
    //                     }
    //                     break;
    //                 }
    //                 case SDLK_RIGHT:
    //                     // Handle right arrow key input
    //                     if (currentSelection < 2)
    //                     {
    //                         currentSelection++;
    //                     }
    //                     break;

    //                 case SDLK_LEFT:
    //                     // Handle left arrow key input
    //                     if (currentSelection > 0)
    //                     {
    //                         currentSelection--;
    //                     }
    //                     break;

    //                 case SDLK_DOWN:
    //                     // Handle down arrow key input
    //                     if (currentSelection > 0)
    //                     {
    //                         currentSelection--;
    //                     }
    //                     break;

    //                 case SDLK_RETURN:
    //                     switch (currentSelection)
    //                     {
    //                     case 0:
    //                         currentState = GameState::Playing;
    //                         loadGameObjectsForState(currentState, gameObjects, renderer, font);
    //                         break;
    //                     }
    //                     break;
    //                 }
    //                 break;
    //             default:
    //                 break;
    //             }
    //             break;
    //             }
    //         }

    //         // Render main menu
    //         // ...
    //         // Render main menu options
    //         SDL_Color white = {255, 255, 255, 255};
    //         SDL_Color dark = {128, 128, 128, 255};

    //         // Render the game objects
    //         for (const auto &object : gameObjects)
    //         {
    //             renderGameObject(renderer, *object);
    //         }


    //         // Update the colors of the game objects based on the current selection
    //         for (int i = 0; i < gameObjects.size(); ++i)
    //         {
    //             TextGameObject *textObject = dynamic_cast<TextGameObject *>(gameObjects[i].get());
    //             if (textObject)
    //             {
    //                 textObject->color = (i == currentSelection) ? white : dark;
    //             }
    //         }

    //         break;
    //     }
    //     case GameState::Playing:
    //     {
    //         // Handle gameplay logic and input
    //         // ...

    //         // Poll events
    //         while (SDL_PollEvent(&event))
    //         {
    //             switch (event.type)
    //             {
    //             case SDL_QUIT:
    //             {
    //                 quit = true;
    //                 break;
    //             }
    //             case SDL_WINDOWEVENT:
    //             {
    //                 switch (event.window.event)
    //                 {
    //                 case SDL_WINDOWEVENT_RESIZED:
    //                 {
    //                     // Get new window dimensions
    //                     int newWidth = event.window.data1;
    //                     int newHeight = event.window.data2;

    //                     // Calculate scaling factors
    //                     float scaleWidth = static_cast<float>(newWidth) / currentWidth;
    //                     float scaleHeight = static_cast<float>(newHeight) / currentHeight;

    //                     // Update the current window size
    //                     currentWidth = newWidth;
    //                     currentHeight = newHeight;

    //                     // Apply the transformation matrix to game objects
    //                     transformGameObjects(gameObjects, Vector2(scaleWidth, scaleHeight));

    //                     // Update the window size
    //                     SDL_SetWindowSize(window, newWidth, newHeight);
    //                     break;
    //                 }
    //                 }
    //                 break;
    //             }
    //             case SDL_KEYDOWN:
    //             {
    //                 switch (event.key.keysym.sym)
    //                 {
    //                 case SDLK_w:
    //                 {
    //                     // handle w press
    //                     break;
    //                 }
    //                 case SDLK_a:
    //                 {
    //                     // handle a press
    //                     break;
    //                 }
    //                 case SDLK_d:
    //                 {
    //                     // handle d press
    //                     break;
    //                 }
    //                 case SDLK_s:
    //                 {
    //                     // handle s press
    //                     break;
    //                 }
    //                 break;
    //                 }
    //             }
    //             break;
    //             }
    //         }

    //         // Render game objects
    //         for (const auto &object : gameObjects)
    //         {
    //             renderGameObject(renderer, *object);
    //         }
    //         // ...
    //         break;
    //     }
    //     case GameState::Paused:
    //     {
    //         // Handle pause menu logic and input
    //         // ...

    //         // Render game objects
    //         // ...
    //         break;
    //     }
    //     }

    //     // Present the back buffer
    //     SDL_RenderPresent(renderer);
    // }

    // // Clean up
    // TTF_CloseFont(font);
    // SDL_DestroyRenderer(renderer);
    // SDL_DestroyWindow(window);
    // SDL_Quit();

    GameManager gameManager;
    gameManager.run();

    return 0;
}
