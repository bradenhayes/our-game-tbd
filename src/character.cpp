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

    jumpSpriteSurface = IMG_Load("../images/Biker_jump.png");
    jumpSpriteTexture = SDL_CreateTextureFromSurface(renderer, jumpSpriteSurface);


    frameRunWidth = runSpriteSurface->w / 6;
    frameRunHeight = runSpriteSurface->h;
    frameJumpWidth = jumpSpriteSurface->w / 4;
    frameJumpHeight = jumpSpriteSurface->h;
    
    characterRect.x = 0;
    characterRect.y = 300;
    characterRect.w = frameRunWidth;
    characterRect.h = frameRunHeight;

    currentFrameIndex = 0;
    frameStartTime = SDL_GetTicks();
    isRunning = false;
    isIdle = true;
    isRunningLeft = false;
    isJumping = false;





}

void Character::startRunning() {
    frameStartTime = SDL_GetTicks();
    isRunning = true;
    isIdle = false;isJumping = false;
}

void Character::stopRunning() {
    currentFrameIndex = 0;
    isRunning = false;
    isIdle = true;isJumping = false;
}


void Character::startRunningLeft() {
    frameStartTime = SDL_GetTicks();
    isRunningLeft = true;
    isIdle = false;isJumping = false;
}

void Character::stopRunningLeft() {
    currentFrameIndex = 0;
    isRunningLeft = false;
    isIdle = true;isJumping = false;
}

void Character::jump() {
    frameStartTime = SDL_GetTicks();
    isJumping = true;
    isIdle = false;
}


void Character::update() {
    Uint32 currentTime = SDL_GetTicks();
    if (isRunning && currentTime - frameStartTime >= FRAME_DELAY) {
        currentFrameIndex = (currentFrameIndex + 1) % FRAME_COUNT;
        frameStartTime = currentTime;
        characterRect.x +=5;
    }
    if (isRunningLeft && currentTime - frameStartTime >= FRAME_DELAY) {
        currentFrameIndex = (currentFrameIndex + 1) % FRAME_COUNT;
        frameStartTime = currentTime;
        characterRect.x -=5;
    }
    if (isIdle && currentTime - frameStartTime >= IDLE_FRAME_DELAY) {
        currentFrameIndex = (currentFrameIndex + 1) % IDLE_FRAME_COUNT;
        frameStartTime = currentTime;
    }
    if (isJumping && currentTime - frameStartTime >= JUMP_FRAME_DELAY) {
        currentFrameIndex = (currentFrameIndex + 1) % JUMP_FRAME_COUNT;
        frameStartTime = currentTime;
        characterRect.y -=3;
        

        
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
    else if (isJumping){
        SDL_Rect sourceRect;
        sourceRect.x = currentFrameIndex * frameJumpWidth;
        sourceRect.y = 0;
        sourceRect.w = frameJumpWidth;
        sourceRect.h = frameJumpHeight;

        SDL_RenderCopy(renderer, jumpSpriteTexture, &sourceRect, &characterRect);
    }
    
}
