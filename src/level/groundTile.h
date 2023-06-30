// GroundTile.h
#pragma once

#include "Tile.h"

class GroundTile : public Tile {
public:
    GroundTile(SDL_Texture* texture);
    void draw(SDL_Renderer* renderer, int x, int y) override;
    // Other GroundTile-specific methods...
};