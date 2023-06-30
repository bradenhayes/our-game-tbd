// Level.cpp
#include "Level.h"

Level::Level(int width, int height)
    : width(width), height(height), tiles(width, std::vector<Tile*>(height, nullptr))
{
    // Initialize the tiles grid with nullptrs
    for (int x = 0; x < width; ++x) {
        for (int y = 0; y < height; ++y) {
            tiles[x][y] = nullptr;
        }
    }
}

Level::~Level()
{
    // Clean up dynamically allocated tiles
    for (int x = 0; x < width; ++x) {
        for (int y = 0; y < height; ++y) {
            delete tiles[x][y];
        }
    }
}

void Level::setTile(int x, int y, Tile* tile)
{
    if (x >= 0 && x < width && y >= 0 && y < height) {
        // Delete the existing tile at the position (if any)
        delete tiles[x][y];
        // Set the new tile at the position
        tiles[x][y] = tile;
    }
}

Tile* Level::getTile(int x, int y)
{
    if (x >= 0 && x < width && y >= 0 && y < height) {
        return tiles[x][y];
    }
    return nullptr;
}

void Level::draw(SDL_Renderer* renderer)
{
    for (int x = 0; x < width; ++x) {
        for (int y = 0; y < height; ++y) {
            Tile* tile = tiles[x][y];
            if (tile != nullptr) {
                tile->draw(renderer, x * TILE_SIZE, y * TILE_SIZE);
            }
        }
    }
}
