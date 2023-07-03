// npc.h

#ifndef NPC_H
#define NPC_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>


class NPC {
public:
    virtual void update() = 0;
    virtual void render(SDL_Renderer* renderer) = 0;
    // Add other common NPC functionality and member variables here
};

class meleeEnemy : public NPC {
public:
    void update() override;
    void render(SDL_Renderer* renderer) override;
    // Add specific enemy functionality and member variables here
};

class NPC1 : public NPC {
public:
    NPC1(SDL_Renderer* renderer); // Constructor that takes the renderer for loading textures
    void update() override;
    void render(SDL_Renderer* renderer) override;
    // Add specific merchant functionality and member variables here

private: 
    SDL_Surface* idleSurface; 
    SDL_Texture* NPC1Texture; // Texture for the merchant sprite
    SDL_Rect NPC1Rect; // Rectangle representing the merchant's position and size 
    int currentFrameIndex;
    Uint32 frameStartTime;
    bool isIdle;
    const int IDLE_FRAME_COUNT = 4;
    const int IDLE_FRAME_DELAY = 1000/15;
};

#endif // NPC_H
