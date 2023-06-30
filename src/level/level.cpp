// Level.cpp
#include "level.h"

Level::Level(int width, int height) : width(width), height(height) {
  tiles.resize(width);
  for (int x = 0; x < width; ++x) {
    tiles[x].resize(height, nullptr);
  }
}

Level::~Level() {
  // No need to manually delete the tiles, std::shared_ptr handles it
  // automatically
}

void Level::setTile(int x, int y, std::shared_ptr<Tile> tile) {
  if (x >= 0 && x < width && y >= 0 && y < height) {
    tiles[x][y] = tile;
  }
}

std::shared_ptr<Tile> Level::getTile(int x, int y) {
  if (x >= 0 && x < width && y >= 0 && y < height) {
    return tiles[x][y];
  }
  return nullptr;
}

void Level::draw(SDL_Renderer *renderer) {
  for (int x = 0; x < width; ++x) {
    for (int y = 0; y < height; ++y) {
      std::shared_ptr<Tile> tile = getTile(x, y);
      if (tile != nullptr) {
        tile->draw(renderer, x * TILE_SIZE, y * TILE_SIZE);
      }
    }
  }
}
