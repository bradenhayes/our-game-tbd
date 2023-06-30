#include <cstdio>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <windows.h>
#include <vector>
#include <string>


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    SDL_Init(SDL_INIT_VIDEO);  // Initialize SDL2

    // Create an application window with the following settings:
    SDL_Window* window = SDL_CreateWindow(
        "Rat Mover 2023",                  // window title
        SDL_WINDOWPOS_UNDEFINED,           // initial x position
        SDL_WINDOWPOS_UNDEFINED,           // initial y position
        800,                               // width, in pixels
        600,                               // height, in pixels
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


     IMG_Init(IMG_INIT_PNG);

    //MESSING WITH SPRITE ANIMATIONS

    // Constants for animation
    const int FRAME_COUNT = 6;
    const int FRAME_DELAY = 100;

    // Load the sprite (   IDLE   )
    SDL_Surface* idleSurface = IMG_Load("../images/Biker_idle1.png");
    if (idleSurface == nullptr) {
        // Error handling
        printf("Failed to load image: %s\n", IMG_GetError());
        return 1;
    }
    SDL_Texture* idleTexture = SDL_CreateTextureFromSurface(renderer, idleSurface);
    SDL_FreeSurface(idleSurface);


    //Load running animation frames
    std::vector<SDL_Surface*> runningFrames;
    for (int i = 1; i <= FRAME_COUNT; ++i) {
        std::string frameFilename = "../images/Biker_run" + std::to_string(i) + ".png";
        runningFrames.push_back(IMG_Load(frameFilename.c_str()));
    }


    // Set up animation variables
    std::vector<SDL_Texture*> runningTextures;
    for (SDL_Surface* surface : runningFrames) {
        runningTextures.push_back(SDL_CreateTextureFromSurface(renderer, surface));
    }

    // Set up character rect
    SDL_Rect characterRect = { 0, 0, 30, 35 };


    SDL_Event event;
    bool quit = false;
    bool isRunning = false;  // Flag to check if running animation is playing
    int currentFrame = 0;
    Uint32 frameStartTime = SDL_GetTicks();  

    while (!quit) {
        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) {
                quit = true;
             }
            else if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_RIGHT) {
                    isRunning = true;
                    frameStartTime = SDL_GetTicks();  // Reset frame start time
                }
            }
        }

       // Clear the renderer
        SDL_RenderClear(renderer);

        // Update the animation frame
        SDL_Texture* currentTexture = idleTexture;
        if (isRunning) {
            Uint32 currentTime = SDL_GetTicks();
            if (currentTime - frameStartTime >= FRAME_DELAY) {
                currentFrame = (currentFrame + 1) % runningTextures.size();
                frameStartTime = currentTime;
            }
            currentTexture = runningTextures[currentFrame];
        }

        // Render the current frame
        SDL_RenderCopy(renderer, currentTexture, NULL, &characterRect);

        // Present the renderer
        SDL_RenderPresent(renderer);
    }

   // Free resources and quit SDL
    SDL_DestroyTexture(idleTexture);
    for (SDL_Texture* texture : runningTextures) {
        SDL_DestroyTexture(texture);
    }
    SDL_FreeSurface(idleSurface);
    for (SDL_Surface* surface : runningFrames) {
        SDL_FreeSurface(surface);
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
}
