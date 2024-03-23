#ifndef _draw
#define _draw

#include <SDL.h>
#include "pong.h"


//draw function
void cleanRender(SDL_Renderer *prenderer, SDL_Window *pwindow);
void drawBall(pongBall *ball, SDL_Renderer *prenderer, SDL_Window *pwindow);
void drawPongElement(pongElement *element, SDL_Renderer *prenderer, SDL_Window *pwindow);

#endif