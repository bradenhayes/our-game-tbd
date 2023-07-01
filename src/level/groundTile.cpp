// GroundTile.cpp
#include "groundTile.h"

GroundTile::GroundTile(SDL_Renderer *renderer, const std::string &imagePath) {
  SDL_Surface *surface = IMG_Load(imagePath.c_str());
  if (surface == nullptr) {
    // Error handling
    printf("Failed to load image: %s\n", IMG_GetError());
    return;
  }
  texture = std::shared_ptr<SDL_Texture>(
      SDL_CreateTextureFromSurface(renderer, surface),
      [](SDL_Texture *texture) {
        SDL_DestroyTexture(texture);
      } // Custom deleter
  );
  SDL_FreeSurface(surface);
}
void GroundTile::draw(SDL_Renderer *renderer, int x, int y) {
  SDL_Rect dstRect = {x, y, TILE_SIZE, TILE_SIZE};
  SDL_RenderCopy(renderer, texture.get(), nullptr, &dstRect);
}