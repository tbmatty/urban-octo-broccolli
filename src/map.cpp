#include "map.hpp"

Map::Map(std::shared_ptr<Grid> grid, std::string mapFile)
    : grid(grid), mapFile(mapFile)
{
    // Load the map data from the file
    std::ifstream file(mapFile);
    if (file.is_open())
    {
        // Determine the dimensions of the map
        std::string line;
        int rowCount = 0;
        int colCount = 0;
        while (std::getline(file, line))
        {
            ++rowCount;
            std::stringstream ss(line);
            std::string tileTypeStr;
            int tempColCount = 0;
            while (std::getline(ss, tileTypeStr, ','))
            {
                ++tempColCount;
            }
            colCount = std::max(colCount, tempColCount);
        }
        file.close();

        // Calculate the unit length based on the screen dimensions and map dimensions
        int unitLength = std::min(grid->getWidth() / colCount, grid->getHeight() / rowCount);
        std::cout << "Unit length set: " << unitLength << std::endl;
        grid->setUnitLength(64);
        std::cout << "Grid unit length: " << grid->getUnitLength() << std::endl;
        // Reopen the file to load the map
        file.open(mapFile);
        int y = 64;
        bool alternating = true;
        while (std::getline(file, line))
        {
            alternating = !alternating;
            std::vector<std::shared_ptr<Tile>> row;
            std::stringstream ss(line);
            std::string tileTypeStr;
            int x = 0;
            while (std::getline(ss, tileTypeStr, ','))
            {
                int tileType = std::stoi(tileTypeStr);

                // Determine tile width and height based on grid cell size
                int tileWidth = grid->getUnitLength();
                int tileHeight = grid->getUnitLength();

                // Create the tile and place it at the correct position in the grid
                if (alternating)
                {
                    auto tile = std::make_shared<Tile>(x * tileWidth, y, tileWidth, tileHeight, tileType);
                    row.push_back(tile);
                    grid->setTile(x, tiles.size(), tile);
                }
                else
                {
                    auto tile = std::make_shared<Tile>((x * tileWidth) + (0.5*tileWidth), y, tileWidth, tileHeight, tileType);
                    row.push_back(tile);
                    grid->setTile(x, tiles.size(), tile);
                }
                ++x;
            }
            tiles.push_back(row);
            y+=32;
        }

        file.close();

        // Set the width and height based on the data
        height = tiles.size();
        width = tiles.empty() ? 0 : tiles[0].size();
    }
}


void Map::Draw(SDL_Renderer *renderer, std::shared_ptr<Viewport> viewport)
{
    // Determine the grid coordinates of the Viewport

    // Iterate over all visible tiles
    std::cout << "at the start of map.draw" << std::endl;
    std::cout << "Viewport->getX(): " << viewport->getX() << std::endl;
    std::cout << "Viewport->getY(): " << viewport->getY() << std::endl;
    std::cout << "Viewport->getWidth(): " << viewport->getWidth() << std::endl;
    std::cout << "Viewport->getHeight(): " << viewport->getHeight() << std::endl;
    // std::cout << "grid.getUnitLength(): " << grid->getUnitLength() << std::endl;
    // std::cout << "grid.getCellHeight(): " << grid.getUnitLength() << std::endl;
    // std::cout << "width: " << width << std::endl;
    // std::cout << "height: " << height << std::endl;


    int startCol = std::floor(std::max(0.0f, viewport->getX() / grid->getUnitLength()));
    int endCol = std::floor(std::min(static_cast<float>(width), (viewport->getX() + viewport->getWidth()) / grid->getUnitLength()));
    int startRow = std::floor(std::max(0.0f, viewport->getY() / grid->getUnitLength()));
    int endRow = std::floor(std::min(static_cast<float>(height), (viewport->getY() + viewport->getHeight()) / grid->getUnitLength()));


    //   // Determine the grid coordinates of the Viewport
    // int startCol = std::floor(std::max(0.0f, viewport->getTopLeft().getV1() / grid->getUnitLength()));
    // int endCol = std::floor(std::min(static_cast<float>(width), viewport->getBottomRight().getV1() / grid->getUnitLength()));
    // int startRow = std::floor(std::max(0.0f, viewport->getTopLeft().getV2() / grid->getUnitLength()));
    // int endRow = std::floor(std::min(static_cast<float>(height), viewport->getBottomRight().getV2()/ grid->getUnitLength()));

    endRow = std::ceil(endRow * 1.5);
    std::cout << "startCol: " << startCol << std::endl;
    std::cout << "endCol: " << endCol << std::endl;
    std::cout << "startRow: " << startRow << std::endl;
    std::cout << "endRow: " << endRow << std::endl;
    // std::cout << "before entering the for loop" << std::endl;


    
    for (int y = startRow; y < endRow; ++y)
    {
        for (int x = startCol; x < endCol; ++x)
        {
            // Load the texture for the tile if it's not already loaded
            if (!tiles[y][x]->hasTexture())
            {
                // this will be commented out for now, we can change it when we do more complex map file types
                // int tileType = tiles[y][x]->getType();
                std::string imagePath = "C:/Users/theba/Documents/2dgameengine/tile.png";
                if (!tiles[y][x]->loadTexture(imagePath, renderer))
                {
                    std::cout << "Failed to load texture for tile at (" << x << ", " << y << ")" << std::endl;
                }
            }

            // Draw the tile
            tiles[y][x]->render(renderer);
        }
    }
}