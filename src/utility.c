#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>

#include "pong.h"

//======================================================
//utility


void utility_error_handler(SDL_Renderer *renderer, SDL_Window *window, char *message)
{
    SDL_Log("Erreure : %s, %s\n", message, SDL_GetError());

    if(renderer != NULL)
    {
        SDL_DestroyRenderer(renderer);
    }

    if(window != NULL)
    {
        SDL_DestroyWindow(window);
    }

    SDL_Quit();
    exit(-1);

}

//------------------------------------------------

SDL_bool utility_bricks_init(game *game)
{
    int bricks_area_width = (*game).width - (2 * (*game).padding);
    int bricks_area_height = ((*game).height * 2) /3;

    int bricks_line_number = bricks_area_width / BRICK_WIDTH;

    int total_gap = bricks_area_width - (BRICK_WIDTH * bricks_line_number);
    (*game).brickGapX = total_gap / (bricks_line_number - 1);

    (*game).brickNumber = bricks_line_number * (bricks_area_height / (*game).brickGapY);

    (*game).bricks = calloc((*game).brickNumber, sizeof(pongElement*));
    if((*game).bricks == NULL)
    {
        return SDL_FALSE;
    }

    return SDL_TRUE;
}

//------------------------------------------------

pongElement* utility_brick_generator(pongElement *pBrick)
{
    pBrick = calloc(1, sizeof(pongElement));
    if(pBrick == NULL)
    {
        return NULL;
    }

    (*pBrick).rectangle.w = BRICK_WIDTH;
    (*pBrick).rectangle.h = BRICK_HEIGHT;
    (*pBrick).colorRGB[0] = BRICK_RGB_R;
    (*pBrick).colorRGB[1] = BRICK_RGB_G;
    (*pBrick).colorRGB[2] = BRICK_RGB_B;

    return pBrick;
}

//------------------------------------------------

void utility_bricks_placement(game *game, SDL_Renderer *prenderer, SDL_Window *pwindow)
{
    int bricks_area_width = (*game).width - (2 * (*game).padding);
    int bricks_line_number = bricks_area_width / BRICK_WIDTH;

    int count = 0;
    int posY = (*game).brickGapY;
    int posX = GAME_PADDING;

    for(int i = 0; i<(*game).brickNumber; i++)
    {
        (*game).bricks[i] = utility_brick_generator((*game).bricks[i]);

        if((*game).bricks[i] == NULL)
        {
            utility_error_handler(prenderer, pwindow, "ERROR when creating a brick");
        }

        if(count >= bricks_line_number)
        {
            count = 0;
            posX = GAME_PADDING;
            posY += (*game).brickGapY;
        }

        (*(*game).bricks[i]).rectangle.x = posX;
        (*(*game).bricks[i]).rectangle.y = posY;

        posX += BRICK_WIDTH + (*game).brickGapX;
        count++;

    }
  
}

//------------------------------------------------

SDL_bool utility_game_clock(game game, Uint64 *program_time)
{
    Uint64 frame_time = SDL_GetTicks64();

    if((frame_time- *program_time) >= game.delta)
    {
        *program_time = frame_time;
        return SDL_TRUE;
    }

    return SDL_FALSE;

    
}

//------------------------------------------------

void utility_free_game(game *game)
{
    for(int i=0; i<(*game).brickNumber; i++)
    {
       free((*game).bricks[i]);
    }

    free((*game).bricks);
    free((*game).score);
}