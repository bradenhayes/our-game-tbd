#ifndef CHARACTER_H
#define CHARACTER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_rect.h>

const int FRAME_COUNT = 6;
const int FRAME_DELAY = 1000/55;
const int IDLE_FRAME_COUNT = 4;
const int IDLE_FRAME_DELAY = 1000/25;
const int JUMP_FRAME_COUNT = 4;
const int JUMP_FRAME_DELAY = 1000/25;

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
    void jump();

private:
    SDL_Renderer* renderer;
    SDL_Surface* idleSurface;
    SDL_Texture* idleTexture;
    SDL_Surface* runSpriteSurface;
    SDL_Texture* runSpriteTexture;
    SDL_Surface* runLeftSpriteSurface;
    SDL_Texture* runLeftSpriteTexture;
    SDL_Surface* jumpSpriteSurface;
    SDL_Texture* jumpSpriteTexture;
    int frameRunWidth;
    int frameRunHeight;
    int frameJumpWidth;
    int frameJumpHeight;
    SDL_Rect characterRect;
    int currentFrameIndex;
    Uint32 frameStartTime;
    bool isRunning;
    bool isIdle;
    bool isRunningLeft;
    bool isJumping;        // Flag indicating if the character is currently jumping
    int startPosY;  // Starting position of the character
    int posY;       // Current position of the character
    int velY;       // Vertical velocity of the character
};

#endif // CHARACTER_H
