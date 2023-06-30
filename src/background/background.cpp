#include "background.h"
#include <SDL2/SDL_image.h>

Background::Background(SDL_Renderer *renderer) {
  // Initialize the SDL image subsystem
  IMG_Init(IMG_INIT_PNG);

  // Create the renderer and set the render draw color to black
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
}

Background::~Background() {
  for (const auto &layer : layers) {
    SDL_DestroyTexture(layer.texture);
  }

  // Quit the SDL image subsystem
  IMG_Quit();
}

void Background::addLayer(const std::string &imagePath, int width, int height,
                          SDL_Renderer *renderer) {
  // Load the image
  SDL_Surface *surface = IMG_Load(imagePath.c_str());
  if (surface == nullptr) {
    // Error handling
    printf("Failed to load image: %s\n", IMG_GetError());
    return;
  }

  // Create the texture
  SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
  SDL_FreeSurface(surface);

  // Set the position and dimensions of the layer
  SDL_Rect position = {0, 0, width, height};

  // Create a new layer and add it to the layers vector
  Layer layer;
  layer.texture = texture;
  layer.position = position;
  layers.push_back(layer);
}

void Background::render(SDL_Renderer *renderer) {
  // Render each layer in reverse order (from back to front)
  for (auto &layer : layers) {
    SDL_RenderCopy(renderer, layer.texture, nullptr, &(layer.position));
  }
}
