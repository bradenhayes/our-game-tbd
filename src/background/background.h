#pragma once

#include <SDL2/SDL.h>
#include <string>
#include <vector>

struct Layer {
  SDL_Texture *texture;
  SDL_Rect position;
};

class Background {
public:
  Background(SDL_Renderer *renderer);
  ~Background();

  void addLayer(const std::string &imagePath, int width, int height,
                SDL_Renderer *renderer);
  void render(SDL_Renderer *renderer);

private:
  std::vector<Layer> layers;
};
