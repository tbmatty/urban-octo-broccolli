#pragma once

#include <SDL.h>
#include <SDL_ttf.h>
#include "text_game_object.hpp"
#include "player_game_object.hpp"
#include <iostream>
#include <memory>
#include <vector>
#include "GameState.hpp"

bool initSDL(SDL_Window *&window, SDL_Renderer *&renderer, const char *title, int width, int height);
SDL_Texture *renderText(SDL_Renderer *renderer, TTF_Font *font, const std::string &text, SDL_Color textColor);
void renderTextGameObject(SDL_Renderer *renderer, TextGameObject &textObject);
void renderGameObject(SDL_Renderer *renderer, GameObject &object);
void transformGameObjects(std::vector<std::unique_ptr<GameObject>>& gameObjects, Vector2 scale);
void renderPlayerGameObject(SDL_Renderer *renderer, GameObject &object);
int loadGameObjectsForState(GameState state, std::vector<std::unique_ptr<GameObject>>& gameObjects, SDL_Renderer* renderer, TTF_Font* font);