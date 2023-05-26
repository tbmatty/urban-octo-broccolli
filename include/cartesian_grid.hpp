#pragma once
#include <vector>
#include <memory>
#include "tile.hpp"

class Grid {
private:
    int width;
    int height;
    int unit_length;
    std::vector<std::vector<std::shared_ptr<Tile>>> tiles;

public:
    Grid(int _width, int _height, int _unit_length);

    void setTile(int x, int y, std::shared_ptr<Tile> tile);
    std::shared_ptr<Tile> getTile(int x, int y);

    int getWidth();
    int getHeight();
    int getUnitLength();
    void setUnitLength(int unit_length);
};
