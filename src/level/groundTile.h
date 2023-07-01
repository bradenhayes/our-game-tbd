// GroundTile.h
#pragma once

#include "tile.h"
#include <memory> // Added for std::shared_ptr
#include <string>


class GroundTile : public Tile {
public:
  GroundTile(SDL_Renderer *renderer, const std::string &imagePath);
  void draw(SDL_Renderer *renderer, int x, int y) override;
  // Other GroundTile-specific methods...

private:
  std::shared_ptr<SDL_Texture> texture;
};