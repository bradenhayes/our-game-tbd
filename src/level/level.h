// Level.h
#pragma once

#include <vector>
#include "tile.h"
#include <memory>  // Added for std::shared_ptr

class Level {
public:
    Level(int width, int height);
    ~Level();

    void setTile(int x, int y, std::shared_ptr<Tile> tile);
    std::shared_ptr<Tile> getTile(int x, int y);
    void draw(SDL_Renderer* renderer);

private:
    int width;
    int height;
    std::vector<std::vector<std::shared_ptr<Tile>>> tiles;
};