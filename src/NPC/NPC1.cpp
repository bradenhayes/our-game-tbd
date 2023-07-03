#include "NPC.h"


NPC1::NPC1(SDL_Renderer* renderer) {
    // Load the merchant texture from file
    idleSurface = IMG_Load("../images/lester/IdleLeft.png");
    NPC1Texture = SDL_CreateTextureFromSurface(renderer, idleSurface);
    SDL_FreeSurface(idleSurface);

     // Set the initial position and size of the merchant
    NPC1Rect.x = 400; // Set the merchant's position
    NPC1Rect.y = 485;
    NPC1Rect.w = idleSurface->w / 4; // Set the merchant's width and height
    NPC1Rect.h = idleSurface->h;
    

    //Setting up animation frames
    currentFrameIndex = 0;
    frameStartTime = SDL_GetTicks(); 

    isIdle = true;
}



void NPC1::update() {
    // Implement NPC update logic here
    Uint32 currentTime = SDL_GetTicks();
    if (isIdle && currentTime - frameStartTime >= IDLE_FRAME_DELAY) {
        
        currentFrameIndex = (currentFrameIndex + 1) % IDLE_FRAME_COUNT;
        frameStartTime = currentTime;

    } 
}


void NPC1::render(SDL_Renderer* renderer) {
    if (isIdle){
         SDL_Rect sourceRect;
        sourceRect.x = currentFrameIndex * NPC1Rect.w;
        sourceRect.y = 0;
        sourceRect.w =  NPC1Rect.w;
        sourceRect.h =  NPC1Rect.h;
        SDL_RenderCopy(renderer, NPC1Texture, &sourceRect, &NPC1Rect);
}
    
}