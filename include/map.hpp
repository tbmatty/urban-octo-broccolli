#pragma once
#include "isometric_grid.hpp"
#include "tile.hpp"
#include "Viewport.hpp"
#include "cartesian_grid.hpp"
#include <fstream>
#include <sstream>
#include <cmath>
#include <vector>
#include <memory>
#include <algorithm>

class Map {
public:
    Map(std::shared_ptr<Grid> grid, std::string mapFile);
    virtual ~Map() = default;

    // void Draw(SDL_Renderer *renderer, std::shared_ptr<Viewport> viewport);
    void Draw(SDL_Renderer *renderer, std::shared_ptr<Viewport> viewport);
private:
    Tile GetTile(int x, int y);

    std::shared_ptr<Grid> grid;
    std::string mapFile;
    std::vector<std::vector<std::shared_ptr<Tile>>> tiles;
    int width;
    int height;
};