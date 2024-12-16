#ifndef _utility
#define _utility

#include <SDL.h>
#include "pong.h"

//utility function
void utility_error_handler(SDL_Renderer *renderer, SDL_Window *window, char *message);

SDL_bool utility_bricks_init(game *game);
pongElement* utility_brick_generator(pongElement *pBrick);
void utility_bricks_placement(game *game, SDL_Renderer *prenderer, SDL_Window *pwindow);
game utility_bricks_saveBrick(game game, pongElement paddle);

SDL_bool utility_game_clock(game game, Uint64 *program_time);

void utility_free_game(game *game);

#endif