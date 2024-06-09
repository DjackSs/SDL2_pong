#ifndef _utility
#define _utility

#include <SDL.h>
#include "pong.h"

//utility function
void utility_error_handler(SDL_Renderer *renderer, SDL_Window *window, char *message);
pongElement* utility_brick_generator(pongElement *pBrick);
void utility_brick_placement(game *game, SDL_Renderer *prenderer, SDL_Window *pwindow);
void utility_clear_brick(pongElement *pBrick);
SDL_bool utility_game_clock(game game, Uint64 *program_time);

#endif