#include <cstdio>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <windows.h>
#include <vector>
#include <string>
#include "character.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window* window = SDL_CreateWindow("Sprite Animation", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_OPENGL);
    if (window == NULL) {
        printf("Could not create window: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    IMG_Init(IMG_INIT_PNG);

    Character character(renderer);

    SDL_Event event;
    bool quit = false;

    Uint32 frameStartTime = SDL_GetTicks();
    Uint32 lastFrameTime = frameStartTime;

    while (!quit) {
        while (SDL_PollEvent(&event) != 0) {

            if (event.type == SDL_QUIT) {
                quit = true;
            }
            else if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_d) {
                    character.startRunning();
                }
                if (event.key.keysym.sym == SDLK_a) {
                    character.startRunningLeft();
                }
                if (event.key.keysym.sym == SDLK_SPACE) {
                    character.jump();
        }
            }
            else if (event.type == SDL_KEYUP) {
                if (event.key.keysym.sym == SDLK_d) {
                    character.stopRunning();
                }
                else if (event.key.keysym.sym == SDLK_a) {
                    character.stopRunningLeft();
                }
            }
        }

        character.update();
        // Clear the renderer
        SDL_RenderClear(renderer);

        character.render();

        SDL_RenderPresent(renderer);

        Uint32 currentFrameTime = SDL_GetTicks();
        Uint32 frameTime = currentFrameTime - lastFrameTime;
        lastFrameTime = currentFrameTime;
        int adjustedFrameDelay = FRAME_DELAY - frameTime;

        // Delay if the frame was rendered too quickly
        if (adjustedFrameDelay > 0) {
            SDL_Delay(adjustedFrameDelay);
        }
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();

    return 0;
}
