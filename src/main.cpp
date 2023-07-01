#include "background/background.h"
#include "level/backgroundTile.h"
#include "level/groundTile.h"
#include "level/level.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <cstdio>
#include <iostream>
#include <memory>
#include <windows.h>
#include <vector>
#include <string>
#include "character.h"
#ifdef _WIN32
#include <direct.h>
#define GETCWD _getcwd
#else
#include <unistd.h>
#define GETCWD getcwd
#endif

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine, int nCmdShow) {
  SDL_Init(SDL_INIT_VIDEO); // Initialize SDL2

  SDL_Window *window =
      SDL_CreateWindow("An SDL2 window",        // window title
                       SDL_WINDOWPOS_UNDEFINED, // initial x position
                       SDL_WINDOWPOS_UNDEFINED, // initial y position
                       SCREEN_WIDTH,            // width, in pixels
                       SCREEN_HEIGHT,           // height, in pixels
                       SDL_WINDOW_OPENGL        // flags - see below
      );

  if (window == NULL) {
    printf("Could not create window: %s\n", SDL_GetError());
    return 1;
  }

  SDL_Renderer *renderer =
      SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

  // Create a background
  Background background(renderer);
  char cwd[1024];
  if (GETCWD(cwd, sizeof(cwd)) != NULL) {
    std::cout << "Current working dir: " << cwd << '\n';
  } else {
    perror("getcwd() error");
    return 1;
  }
  // Add the background layers
  background.addLayer("../images/layer1.png", SCREEN_WIDTH, SCREEN_HEIGHT,
                      renderer);
  background.addLayer("../images/layer2.png", SCREEN_WIDTH, SCREEN_HEIGHT,
                      renderer);
  background.addLayer("../images/layer3.png", SCREEN_WIDTH, SCREEN_HEIGHT,
                      renderer);
  background.addLayer("../images/layer4.png", SCREEN_WIDTH, SCREEN_HEIGHT,
                      renderer);
  background.addLayer("../images/layer5.png", SCREEN_WIDTH, SCREEN_HEIGHT,
                      renderer);

  // Create a level with a width and height that fills the screen
  Level level(SCREEN_WIDTH / TILE_SIZE, SCREEN_HEIGHT / TILE_SIZE);

  // Add a ground tile at the bottom of the screen
  for (int x = 0; x < SCREEN_WIDTH / TILE_SIZE; ++x) {
    level.setTile(x, SCREEN_HEIGHT / TILE_SIZE - 1,
                  std::make_shared<GroundTile>(
                      renderer, "../images/IndustrialTile_73.png"));
  }

  // Add background tiles
  for (int x = 0; x < SCREEN_WIDTH / TILE_SIZE; ++x) {
    level.setTile(x, SCREEN_HEIGHT / TILE_SIZE - 3,
                  std::make_shared<BackgroundTile>(
                      renderer, "../images/IndustrialTile_02.png"));
  }


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
