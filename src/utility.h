#ifndef _utility
#define _utility

#include <SDL.h>
#include "pong.h"

//utility function
void errorHandeler(SDL_Renderer *renderer, SDL_Window *window, char *message);
pongElement* brickGenerator(pongElement *pBrick);
void brickplacement(game *game, SDL_Renderer *prenderer, SDL_Window *pwindow);
void clearBrick(pongElement *pBrick);

#endif