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
        int y = -64;
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
                    auto tile = std::make_shared<Tile>((x * tileWidth) - 32, y, tileWidth, tileHeight, tileType, (x * tileWidth) - 32, y);
                    row.push_back(tile);
                    grid->setTile(x, tiles.size(), tile);
                }
                else
                {
                    auto tile = std::make_shared<Tile>(((x * tileWidth) + (0.5 * tileWidth)) - 32, y, tileWidth, tileHeight, tileType, ((x * tileWidth) + (0.5 * tileWidth)) - 32, y);
                    row.push_back(tile);
                    grid->setTile(x, tiles.size(), tile);
                }
                ++x;
            }
            tiles.push_back(row);
            y += 32;
        }

        file.close();

        // Set the width and height based on the data
        height = tiles.size();
        width = tiles.empty() ? 0 : tiles[0].size();
    }
}

void Map::Draw(SDL_Renderer *renderer, std::shared_ptr<Viewport> viewport)
{

    std::cout << "at the start of map.draw" << std::endl;

    // Find the indices for the tiles we want to draw
    // We have the top left coordinates of the viewport, and also the bottom right
    // With this information, and the knowledge of the width and height of the tiles,
    // We can express the range along the x axis. Consider the following example:
    // The viewport top left is (600, 800) and the bottom right is (600+k, 800+l)
    // We know the height of a tile is 32, and the width is 64
    // So the range along the x axis is (600, 600+k), which can be expressed as
    // 600 -> 600+k ~= (n*tileWidth) -> ((n+k)*tileWidth)
    // So we can find the range of tiles to draw by finding the value of n
    // We can find n by dividing 600 by the tile width, and rounding down
    // We know the bottom right of the viewport values with viewport->getBottomRight(), so we can get k from that
    // We can then iterate from n to n+k, and draw the tiles at those indices
    // We can do similarly for the y axis, where the range is (800, 800+l)
    // We can find the value of m by dividing 800 by the tile height, and rounding down
    // We can find l from the bottom right of the viewport, and then iterate from m to m+l
    // We can then draw the tiles at those indices

    // along the x axis, we want to iterate from n to n+k
    int n = std::floor(viewport->getTopLeft().getV1() / grid->getUnitLength());
    int k = std::floor(viewport->getBottomRight().getV1() / grid->getUnitLength());

    // along the y axis, we want to iterate from m to m+l
    int m = std::floor(viewport->getTopLeft().getV2() / 32);
    int l = std::floor(viewport->getBottomRight().getV2() / 32);

    // Determine the grid coordinates of the Viewport

    // Iterate over all visible tiles
    std::cout << "Viewport->getX(): " << viewport->getX() << std::endl;
    std::cout << "Viewport->getY(): " << viewport->getY() << std::endl;
    std::cout << "Viewport->getWidth(): " << viewport->getWidth() << std::endl;
    std::cout << "Viewport->getHeight(): " << viewport->getHeight() << std::endl;
    std::cout << "grid.getUnitLength(): " << grid->getUnitLength() << std::endl;
    std::cout << "grid.getCellHeight(): " << grid->getUnitLength() << std::endl;
    std::cout << "width: " << width << std::endl;
    std::cout << "height: " << height << std::endl;

    int startCol = std::floor(std::max(0.0f, viewport->getX() / grid->getUnitLength())) - 1;
    int endCol = std::floor(std::min(static_cast<float>(width), (viewport->getX() + viewport->getWidth()) / grid->getUnitLength())) + 1;
    int startRow = std::floor(std::max(0.0f, viewport->getY() / grid->getUnitLength())) - 1;
    int endRow = std::floor(std::min(static_cast<float>(height), (viewport->getY() + viewport->getHeight()) / grid->getUnitLength())) + 1;

    if (n < 0)
    {
        n = 0;
    }
    if (m < 0)
    {
        m = 0;
    }
    std::cout << "n: " << n << std::endl;
    std::cout << "k: " << k << std::endl;
    std::cout << "m: " << m << std::endl;
    std::cout << "l: " << l << std::endl;

    endRow = std::ceil(endRow * 1.5);
    std::cout << "startCol: " << startCol << std::endl;
    std::cout << "endCol: " << endCol << std::endl;
    std::cout << "startRow: " << startRow << std::endl;
    std::cout << "endRow: " << endRow << std::endl;
    // std::cout << "before entering the for loop" << std::endl;

    // startRow = 5;
    endRow = 20;

    startCol = n;
    endCol = k;

    startRow = m;
    endRow = l + 2;

    int screenY = -64;
    bool alternating = true;
    int tileWidth = grid->getUnitLength();
    int tileHeight = grid->getUnitLength() / 2;
    for (int y = startRow; y <= endRow; ++y)
    {
        alternating = !alternating;
        int screenX = 0;
        for (int x = startCol; x <= endCol; ++x)
        {
            if (alternating)
            {
                tiles[y][x]->setScreenX((screenX * tileWidth) - 32);
                tiles[y][x]->setScreenY(screenY);
            }
            else
            {
                tiles[y][x]->setScreenX(((screenX * tileWidth) + (0.5 * tileWidth)) - 32);
                tiles[y][x]->setScreenY(screenY);
            }
            ++screenX;
            // Load the texture for the tile if it's not already loaded
            if (!tiles[y][x]->hasTexture())
            {
                // this will be commented out for now, we can change it when we do more complex map file types
                int tileType = tiles[y][x]->getType();
                std::string imagePath;
                if(tileType == 0)
                {
                    imagePath = "C:/Users/theba/Documents/2dgameengine/tile.png";
                }
                else if(tileType == 1)
                {
                    imagePath = "C:/Users/theba/Documents/2dgameengine/tile2.png";
                }
                if (!tiles[y][x]->loadTexture(imagePath, renderer))
                {
                    std::cout << "Failed to load texture for tile at (" << x << ", " << y << ")" << std::endl;
                }
            }
            // Draw the tile
            tiles[y][x]->render(renderer);
        }
        screenY += 32;
    }

    std::cout << "the tile at position n,m" << std::endl;
    std::cout << "tiles[n][m]->getScreenX(): " << tiles[n][m]->getScreenX() << std::endl;
    std::cout << "tiles[n][m]->getScreenY():" << tiles[n][m]->getScreenY() << std::endl;
}