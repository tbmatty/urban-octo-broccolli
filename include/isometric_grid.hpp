#pragma once
#include "vector2.hpp"

class IsometricGrid {
public:
    IsometricGrid(int cellWidth, int cellHeight, int width, int height);
    virtual ~IsometricGrid() = default;

    Vector2 GridToScreen(int gridX, int gridY) const;
    Vector2 ScreenToGrid(int screenX, int screenY) const;

    int getCellWidth();
    int getCellHeight();
    // int getHeight();
    // int getWidth();
    // Vector2 FindSpawnPlace() const;

    // Vector2 FindCellAtDistance(int gridX, int gridY, int distance) const;

private:
    int width;
    int height;
    int cellWidth;
    int cellHeight;
};