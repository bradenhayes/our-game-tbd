// BackgroundTile.h
#pragma once

#include "tile.h"
#include <string>
#include <memory>  // Added for std::shared_ptr

class BackgroundTile : public Tile {
public:
    BackgroundTile(SDL_Renderer* renderer, const std::string& imagePath);
    void draw(SDL_Renderer* renderer, int x, int y) override;
    // Other BackgroundTile-specific methods...

private:
    std::shared_ptr<SDL_Texture> texture;
};