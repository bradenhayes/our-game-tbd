#include "character.h"
#include <cstdio>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <windows.h>
#include <vector>
#include <string>



Character::Character(SDL_Renderer* renderer) : renderer(renderer) {

    //Loading Image Textures
    idleSurface = IMG_Load("../images/Biker_idle.png");
    idleTexture = SDL_CreateTextureFromSurface(renderer, idleSurface);
    SDL_FreeSurface(idleSurface);

    idleLeftSurface = IMG_Load("../images/Biker_idleLeft.png");
    idleLeftTexture = SDL_CreateTextureFromSurface(renderer, idleLeftSurface);
    SDL_FreeSurface(idleLeftSurface);

    runSpriteSurface = IMG_Load("../images/Biker_run.png");
    runSpriteTexture = SDL_CreateTextureFromSurface(renderer, runSpriteSurface);

    runLeftSpriteSurface = IMG_Load("../images/Biker_runLeft.png");
    runLeftSpriteTexture = SDL_CreateTextureFromSurface(renderer, runLeftSpriteSurface);

    jumpSpriteSurface = IMG_Load("../images/Biker_jump.png");
    jumpSpriteTexture = SDL_CreateTextureFromSurface(renderer, jumpSpriteSurface);


    //Setting frame sizes for each animation frame (each sprite .png contains all n number of frames)
    frameRunWidth = runSpriteSurface->w / 6;
    frameRunHeight = runSpriteSurface->h;
    frameJumpWidth = jumpSpriteSurface->w / 4;
    frameJumpHeight = jumpSpriteSurface->h;
    
    //Initial character x y size and location
    characterRect.x = 0;
    characterRect.y = 500;
    characterRect.w = frameRunWidth;
    characterRect.h = frameRunHeight;


    //Jumping Variables
    jumpHeight = characterRect.y + 50;
    jumpSpeed = 30;
    gravity = -2;
    groundHeight = 500;


    //Setting up animation frames
    currentFrameIndex = 0;
    frameStartTime = SDL_GetTicks(); 
    // retrieves the current system time in milliseconds using the SDL_GetTicks() function and assigns it to the frameStartTime variable. 
    //keep track of the starting time of a particular animation frame. 
    // called when a specific animation starts or needs to be updated.


    //Animation Flags
    isRunning = false;
    isIdle = true;
    isIdleLeft = false;
    isRunningLeft = false;
    isJumping = false;

}

//method triggered when character is moving right direction
void Character::startRunning() {
    frameStartTime = SDL_GetTicks();
    isRunning = true;
    isIdle = false;isJumping = false;
    isIdleLeft = false;
}
//method triggered when character is no longer moving right (no keypress on right movement detected)
void Character::stopRunning() {
    currentFrameIndex = 0;
    isRunning = false;
    isIdle = true;isJumping = false;
}


void Character::startRunningLeft() {
    frameStartTime = SDL_GetTicks();
    isRunningLeft = true;
    isIdle = false;isJumping = false;
    isIdleLeft = false;
}

void Character::stopRunningLeft() {
    currentFrameIndex = 0;
    isRunningLeft = false;
    isIdle = true;isJumping = false;
    isIdleLeft = true;
}

//Method for player to jump (space bar)
void Character::jump() {
    frameStartTime = SDL_GetTicks();
    isJumping = true;
    isIdle = false;
}

//updating the character's animation based on the elapsed time and the animation flags. 
//calculates the current frame index for the active animation and updates the character's position accordingly.
void Character::update() {
    Uint32 currentTime = SDL_GetTicks();

    //RIGHT MOVEMENT
    if (isRunning && currentTime - frameStartTime >= FRAME_DELAY) {
        currentFrameIndex = (currentFrameIndex + 1) % FRAME_COUNT;
        frameStartTime = currentTime;
        characterRect.x +=5;
    }
    //LEFT MOVEMENT
    if (isRunningLeft && currentTime - frameStartTime >= FRAME_DELAY) {
        currentFrameIndex = (currentFrameIndex + 1) % FRAME_COUNT;
        frameStartTime = currentTime;
        characterRect.x -=5;
    }
    //NO KEYPRESS
    if ((isIdle || isIdleLeft) && currentTime - frameStartTime >= IDLE_FRAME_DELAY) {
        currentFrameIndex = (currentFrameIndex + 1) % IDLE_FRAME_COUNT;
        frameStartTime = currentTime;
    }

    //JUMP 
    if (isJumping && currentTime - frameStartTime >= JUMP_FRAME_DELAY) {
        currentFrameIndex = (currentFrameIndex + 1) % JUMP_FRAME_COUNT;
        frameStartTime = currentTime;

        characterRect.y -= jumpSpeed;
        jumpHeight -= jumpSpeed;
        jumpSpeed += gravity;

        if (jumpHeight <= 0){
            characterRect.y = groundHeight;
            isJumping = false;
            jumpHeight = 0;
            jumpSpeed = 0;
        }
        characterRect.x +=5;
        characterRect.x -=5;
        
    }


    // GROUND COLLISION
    // Check for collision between character and ground tile
}


//rendering the character's sprite based on its current state (isRunning, isRunningLeft, isIdle, isJumping) 
//and the current frame index (currentFrameIndex).
void Character::render() {

    //RIGHT MOVEMENT RENDER
    if (isRunning){
        SDL_Rect sourceRect;
        sourceRect.x = currentFrameIndex * frameRunWidth;
        sourceRect.y = 0;
        sourceRect.w = frameRunWidth;
        sourceRect.h = frameRunHeight;

        SDL_RenderCopy(renderer, runSpriteTexture, &sourceRect, &characterRect);
    }

    //LEFT MOVEMENT RENDER
    else if (isRunningLeft){
        SDL_Rect sourceRect;
        sourceRect.x = currentFrameIndex * frameRunWidth;
        sourceRect.y = 0;
        sourceRect.w = frameRunWidth;
        sourceRect.h = frameRunHeight;

        SDL_RenderCopy(renderer, runLeftSpriteTexture, &sourceRect, &characterRect);
    }

    // IDLE RIGHT FACING RENDER
    else if (isIdle && !isIdleLeft){
        SDL_Rect sourceRect;
        sourceRect.x = currentFrameIndex * frameRunWidth;
        sourceRect.y = 0;
        sourceRect.w = frameRunWidth;
        sourceRect.h = frameRunHeight;

        SDL_RenderCopy(renderer, idleTexture, &sourceRect, &characterRect);
    }

    // IDLE LEFT FACING RENDER
    else if (isIdle && isIdleLeft){
        SDL_Rect sourceRect;
        sourceRect.x = currentFrameIndex * frameRunWidth;
        sourceRect.y = 0;
        sourceRect.w = frameRunWidth;
        sourceRect.h = frameRunHeight;

        SDL_RenderCopy(renderer, idleLeftTexture, &sourceRect, &characterRect);
    }

    // JUMP RENDER
    else if (isJumping){
        SDL_Rect sourceRect;
        sourceRect.x = currentFrameIndex * frameJumpWidth;
        sourceRect.y = 0;
        sourceRect.w = frameJumpWidth;
        sourceRect.h = frameJumpHeight;

        SDL_RenderCopy(renderer, jumpSpriteTexture, &sourceRect, &characterRect);
    }
    
}
