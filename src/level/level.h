// Level.h
#pragma once

#include <vector>
#include "Tile.h"

class Level {
public:
    Level(int width, int height);
    ~Level();

    void setTile(int x, int y, Tile* tile);
    Tile* getTile(int x, int y);
    void draw(SDL_Renderer* renderer);

private:
    int width, height;
    std::vector<std::vector<Tile*>> tiles;
};
