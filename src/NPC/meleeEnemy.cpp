#include "NPC.h"

void meleeEnemy::update() {
    // Implement enemy update logic here


    
}


void meleeEnemy::render(SDL_Renderer* renderer) {
    // Implement enemy rendering logic here using the provided renderer
    // For example:
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Red color
    SDL_Rect enemyRect;
    enemyRect.x = 700; // Set the enemy's position
    enemyRect.y = 500;
    enemyRect.w = 32; // Set the enemy's width and height
    enemyRect.h = 32;
    SDL_RenderFillRect(renderer, &enemyRect); // Render the enemy as a filled rectangle
}