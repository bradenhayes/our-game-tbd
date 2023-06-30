#include "character.h"
#include <cstdio>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <windows.h>
#include <vector>
#include <string>

Character::Character(SDL_Renderer* renderer) : renderer(renderer) {
    idleSurface = IMG_Load("../images/Biker_idle.png");
    idleTexture = SDL_CreateTextureFromSurface(renderer, idleSurface);
    SDL_FreeSurface(idleSurface);

    runSpriteSurface = IMG_Load("../images/Biker_run.png");
    runSpriteTexture = SDL_CreateTextureFromSurface(renderer, runSpriteSurface);
    runLeftSpriteSurface = IMG_Load("../images/Biker_runLeft.png");
    runLeftSpriteTexture = SDL_CreateTextureFromSurface(renderer, runLeftSpriteSurface);
    frameRunWidth = runSpriteSurface->w / 6;
    frameRunHeight = runSpriteSurface->h;
    characterRect.x = 0;
    characterRect.y = 0;
    characterRect.w = frameRunWidth;
    characterRect.h = frameRunHeight;

    currentFrameIndex = 0;
    frameStartTime = SDL_GetTicks();
    isRunning = false;
}

void Character::startRunning() {
    frameStartTime = SDL_GetTicks();
    isRunning = true;
    isIdle = false;
}

void Character::stopRunning() {
    currentFrameIndex = 0;
    isRunning = false;
    isIdle = true;
}


void Character::startRunningLeft() {
    frameStartTime = SDL_GetTicks();
    isRunningLeft = true;
    isIdle = false;
}

void Character::stopRunningLeft() {
    currentFrameIndex = 0;
    isRunningLeft = false;
    isIdle = true;
}

void Character::update() {
    Uint32 currentTime = SDL_GetTicks();
    if (isRunning && currentTime - frameStartTime >= FRAME_DELAY) {
        currentFrameIndex = (currentFrameIndex + 1) % FRAME_COUNT;
        frameStartTime = currentTime;
    }
    if (isRunningLeft && currentTime - frameStartTime >= FRAME_DELAY) {
        currentFrameIndex = (currentFrameIndex + 1) % FRAME_COUNT;
        frameStartTime = currentTime;
    }
    if (isIdle && currentTime - frameStartTime >= IDLE_FRAME_DELAY) {
        currentFrameIndex = (currentFrameIndex + 1) % IDLE_FRAME_COUNT;
        frameStartTime = currentTime;
    }
}


void Character::render() {
    if (isRunning){
        SDL_Rect sourceRect;
        sourceRect.x = currentFrameIndex * frameRunWidth;
        sourceRect.y = 0;
        sourceRect.w = frameRunWidth;
        sourceRect.h = frameRunHeight;

        SDL_RenderCopy(renderer, runSpriteTexture, &sourceRect, &characterRect);
    }
    else if (isRunningLeft){
        SDL_Rect sourceRect;
        sourceRect.x = currentFrameIndex * frameRunWidth;
        sourceRect.y = 0;
        sourceRect.w = frameRunWidth;
        sourceRect.h = frameRunHeight;

        SDL_RenderCopy(renderer, runLeftSpriteTexture, &sourceRect, &characterRect);
    }
    else if (isIdle){
        SDL_Rect sourceRect;
        sourceRect.x = currentFrameIndex * frameRunWidth;
        sourceRect.y = 0;
        sourceRect.w = frameRunWidth;
        sourceRect.h = frameRunHeight;

        SDL_RenderCopy(renderer, idleTexture, &sourceRect, &characterRect);
    }
    
}
