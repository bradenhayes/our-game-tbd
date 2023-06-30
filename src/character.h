#ifndef CHARACTER_H
#define CHARACTER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

const int FRAME_COUNT = 6;
const int FRAME_DELAY = 1000/55;
const int IDLE_FRAME_COUNT = 4;
const int IDLE_FRAME_DELAY = 1000/25;

class Character {
public:
    Character(SDL_Renderer* renderer);
    void idle();
    void startRunning();
    void stopRunning();
    void startRunningLeft();
    void stopRunningLeft();
    void update();
    void render();

private:
    SDL_Renderer* renderer;
    SDL_Surface* idleSurface;
    SDL_Texture* idleTexture;
    SDL_Surface* runSpriteSurface;
    SDL_Texture* runSpriteTexture;
    SDL_Surface* runLeftSpriteSurface;
    SDL_Texture* runLeftSpriteTexture;
    int frameRunWidth;
    int frameRunHeight;
    SDL_Rect characterRect;
    int currentFrameIndex;
    Uint32 frameStartTime;
    bool isRunning;
    bool isIdle;
    bool isRunningLeft;
};

#endif // CHARACTER_H
