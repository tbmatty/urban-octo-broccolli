#include "cartesian_grid.hpp"
#include "tile.hpp"

Grid::Grid(int _width, int _height, int _unit_length) : width(_width), height(_height), unit_length(_unit_length) {
    tiles = std::vector<std::vector<std::shared_ptr<Tile>>>(height, std::vector<std::shared_ptr<Tile>>(width, nullptr));
}

void Grid::setTile(int x, int y, std::shared_ptr<Tile> tile) {
    if (x >= 0 && x < width && y >= 0 && y < height) {
        tiles[y][x] = tile;
    }
}

std::shared_ptr<Tile> Grid::getTile(int x, int y) {
    if (x >= 0 && x < width && y >= 0 && y < height) {
        return tiles[y][x];
    }
    return nullptr;
}

int Grid::getWidth() { return width; }
int Grid::getHeight() { return height; }
int Grid::getUnitLength() { return unit_length; }
void Grid::setUnitLength( int unit_length ){ this->unit_length = unit_length; }