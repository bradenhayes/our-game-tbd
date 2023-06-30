// Tile.h
#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

const int TILE_SIZE = 32; // This can be whatever you need for your game

class Tile {
public:
    virtual ~Tile() = default;

    // Virtual draw function to be overridden by child classes
    virtual void draw(SDL_Renderer* renderer, int x, int y) = 0;
};
