#include "isometric_grid.hpp"

IsometricGrid::IsometricGrid(int cellWidth, int cellHeight, int width, int height)
    : cellWidth(cellWidth), cellHeight(cellHeight), width(width), height(height){};

Vector2 IsometricGrid::GridToScreen(int gridX, int gridY) const
{
    int screenX = (gridX - gridY) * (cellWidth / 2) + (width / 2);
    int screenY = (gridX + gridY) * (cellHeight / 2);
    return Vector2(screenX, screenY);
}

// Vector2 IsometricGrid::GridToScreen(int gridX, int gridY) const
// {
//     int screenX = ((gridX - gridY) * (cellWidth / 2)) + (width / 2);
//     int screenY = ((gridX + gridY) * (cellHeight / 2));
//     return Vector2(screenX, screenY);
// }


Vector2 IsometricGrid::ScreenToGrid(int screenX, int screenY) const
{
    int gridX = (screenY / cellHeight) + (screenX / cellWidth);
    int gridY = (screenY / cellHeight) - (screenX / cellWidth);
    return Vector2(gridX, gridY);
}

int IsometricGrid::getCellWidth(){ return cellWidth; }
int IsometricGrid::getCellHeight(){ return cellHeight; };
// int IsometricGrid::getHeight(){ return height; }
// int IsometricGrid::getWidth(){ return width; }


// Vector2 IsometricGrid::FindSpawnPlace() const
// {
//     // TODO: Implement
// }

// Vector2 IsometricGrid::FindCellAtDistance(int gridX, int gridY, int distance) const
// {
//     //TODO: Implement
// }