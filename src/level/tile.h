#pragma once
#include <SDL2/SDL2.h>

class Tile {
    public:
        virtual void draw(SDL_Renderer* renderer, int x, int y) = 0;  // Pure virtual function

    protected:
        SDL_Texture* texture;
}
