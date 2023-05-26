#pragma once

#include <SDL.h>
#include <SDL_ttf.h>
#include <vector>
#include <memory>
#include <unordered_map>
#include "game_object.hpp"
#include "text_game_object.hpp"
#include "player_game_object.hpp"
#include "viewport.hpp"
#include "GameState.hpp"
#include "cartesian_grid.hpp"
#include "map.hpp"

class GameManager {
public:
    GameManager();
    ~GameManager();

    void run();


private:

    SDL_Window *window;
    SDL_Renderer *renderer;
    TTF_Font *font;
    int currentWidth, currentHeight;
    int currentSelection;
    bool quit;
    Uint32 frameStart;
    float deltaTime;
    GameState currentState;
    std::shared_ptr<GameObject> playerObject;
    std::vector<std::shared_ptr<GameObject>> gameObjects;
    std::shared_ptr<Viewport> viewport;
    std::unique_ptr<Map> map;
    std::shared_ptr<Grid> grid;

    void handleMainMenuEvent(const SDL_Event &event);
    void handlePlayingEvent(const SDL_Event &event);
    void handlePausedEvent(const SDL_Event &event);
    void handleWindowResizing(int newWidth, int newHeight);
    void scaleGameObjects(const Vector2 &scale);
    bool initSDL(SDL_Window *&window, SDL_Renderer *&renderer, const char *title, int width, int height);
    int loadGameObjectsForState(GameState state);
    void renderGameObject(SDL_Renderer *renderer, GameObject &object);
    void pollEvents();
    void updateAndRender();
};