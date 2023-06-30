#include <cstdio>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <windows.h>
#include <vector>
#include <string>
// Define the desired frame rate
const int FPS = 60;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    SDL_Init(SDL_INIT_VIDEO);  // Initialize SDL2

    // Create an application window with the following settings:
    SDL_Window* window = SDL_CreateWindow(
        "Sprite Animation",                  // window title
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
    const int FRAME_DELAY = 60;

    // Load the sprite (   IDLE   )
    SDL_Surface* idleSurface = IMG_Load("../images/Biker_idle.png");
    if (idleSurface == nullptr) {
        // Error handling
        printf("Failed to load image: %s\n", IMG_GetError());
        return 1;
    }
    SDL_Texture* idleTexture = SDL_CreateTextureFromSurface(renderer, idleSurface);
    SDL_FreeSurface(idleSurface);

    SDL_Surface* runSpriteSurface = IMG_Load("../images/Biker_run.png");
    if (runSpriteSurface== nullptr) {
        // Error handling
        printf("Failed to load sprite sheet image: %s\n", IMG_GetError());
        return 1;
    }

    SDL_Texture* runSpriteTexture = SDL_CreateTextureFromSurface(renderer, runSpriteSurface);
    if (runSpriteTexture == nullptr) {
        // Error handling
        printf("Failed to create sprite sheet texture: %s\n", SDL_GetError());
        SDL_FreeSurface(runSpriteSurface);
        return 1;
    }


    int frameWidth = runSpriteSurface->w / 6;
    int frameHeight = runSpriteSurface->h;


    SDL_Rect sourceRect;
    SDL_Rect characterRect;

    // Set up character rect
    characterRect.x = 0;            // Initial X position of the character
    characterRect.y = 0;            // Initial Y position of the character
    characterRect.w = frameWidth;   // Width of the character frame
    characterRect.h = frameHeight;  // Height of the character frame

    //animation variables
    int currentFrameIndex = 0;  // Initialize the counter
    Uint32 frameStartTime = SDL_GetTicks(); 
    Uint32 frameEndTime;
    int currentFrame = 0;
    Uint32 lastFrameTime = SDL_GetTicks();  // Initialize lastFrameTime


    //Game Loop Variables
    SDL_Event event;
    bool quit = false;
    bool isRunning;
 


  

    while (!quit) {

        //handle events and game logic 
        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) {
                quit = true;
            }
            else if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_RIGHT) {
                    frameStartTime = SDL_GetTicks();  // Reset frame start time
                    isRunning = true; 
                }
            }

            else if (event.type == SDL_KEYUP) {
                if (event.key.keysym.sym == SDLK_RIGHT) {
                    currentFrameIndex = 0;  // Set the frame index back to 0 when the right arrow key is released
                    isRunning = false;
                }
            }
        }

       // Clear the renderer
        SDL_RenderClear(renderer);

        // Update the animation frame
        if (isRunning) {
            Uint32 currentTime = SDL_GetTicks();
            if (currentTime - frameStartTime >= FRAME_DELAY) {
                currentFrameIndex = (currentFrameIndex + 1) % FRAME_COUNT;  // Move to the next frame
                frameStartTime = currentTime;
            }
        }
        // Set the source rectangle to extract the current frame from the sprite sheet
        sourceRect.x = currentFrameIndex * frameWidth;
        sourceRect.y = 0;
        sourceRect.w = frameWidth;
        sourceRect.h = frameHeight;


        // Render the current frame
        SDL_RenderCopy(renderer, runSpriteTexture, &sourceRect, &characterRect);


        // Present the renderer
        SDL_RenderPresent(renderer);


        // Calculate the frame time
        Uint32 currentFrameTime = SDL_GetTicks();
        Uint32 frameTime = currentFrameTime - lastFrameTime;
        lastFrameTime = currentFrameTime;

        // Delay if the frame was rendered too quickly
        if (frameTime < FRAME_DELAY) {
            SDL_Delay(FRAME_DELAY - frameTime);
        }   

        frameStartTime = frameEndTime;
    }

   // Free resources and quit SDL
    SDL_FreeSurface(runSpriteSurface);
    SDL_DestroyTexture(runSpriteTexture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
}
