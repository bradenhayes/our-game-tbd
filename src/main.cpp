#include <cstdio>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <windows.h>


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    SDL_Init(SDL_INIT_VIDEO);  // Initialize SDL2

    // Create an application window with the following settings:
    SDL_Window* window = SDL_CreateWindow(
        "Rat Mover 2023",                  // window title
        SDL_WINDOWPOS_UNDEFINED,           // initial x position
        SDL_WINDOWPOS_UNDEFINED,           // initial y position
        640,                               // width, in pixels
        480,                               // height, in pixels
        SDL_WINDOW_OPENGL                  // flags - see below
    );

    // Check that the window was successfully created
    if (window == NULL) {
        // In the case that the window could not be made...
        printf("Could not create window: %s\n", SDL_GetError());
        return 1;
    }

    // Create a renderer
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    // Load the sprite
    const char* imagePath = "../images/rat.png";
    SDL_Surface* surface = IMG_Load(imagePath);
    if (surface == nullptr) {
        // Error handling
        printf("Failed to load image: %s\n", IMG_GetError());
        return 1;
    }
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    // Create a source rectangle for the sprite
    SDL_Rect srcRect;
    SDL_QueryTexture(texture, NULL, NULL, &srcRect.w, &srcRect.h);
    srcRect.x = 0;
    srcRect.y = 0;

    // Create a destination rectangle for the sprite
    SDL_Rect dstRect = { 100, 100, srcRect.w, srcRect.h };

    SDL_Event event;
    bool quit = false;

    while (!quit) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = true;
            } else if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                    case SDLK_LEFT: dstRect.x -= 5; break;
                    case SDLK_RIGHT: dstRect.x += 5; break;
                    case SDLK_UP: dstRect.y -= 5; break;
                    case SDLK_DOWN: dstRect.y += 5; break;
                }
            }
        }

        // Render the sprite
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, texture, &srcRect, &dstRect);
        SDL_RenderPresent(renderer);
    }

    // Close and destroy the window
    SDL_DestroyWindow(window);

    // Clean up
    SDL_Quit();
    return 0;
}
