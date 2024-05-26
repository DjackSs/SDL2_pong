#ifndef _draw
#define _draw

#include <SDL.h>
#include "pong.h"


//draw function
void draw_clean_render(SDL_Renderer *prenderer, SDL_Window *pwindow);
void draw_ball(pongBall *ball, SDL_Renderer *prenderer, SDL_Window *pwindow);
void draw_pong_element(pongElement *element, SDL_Renderer *prenderer, SDL_Window *pwindow);

#endif