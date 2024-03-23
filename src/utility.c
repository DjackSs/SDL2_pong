#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>

#include "pong.h"

//======================================================
//utility


void errorHandeler(SDL_Renderer *renderer, SDL_Window *window, char *message)
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

pongElement* brickGenerator(pongElement *pBrick)
{
    int width = 100;
    int height = 20;
    int red = 215;
    int green = 24;
    int blue = 202;

    pBrick = calloc(1, sizeof(pongElement));
    if(pBrick == NULL)
    {
        return NULL;
    }

    (*pBrick).rectangle.w = width;
    (*pBrick).rectangle.h = height;
    (*pBrick).colorRGB[0] = red;
    (*pBrick).colorRGB[1] = green;
    (*pBrick).colorRGB[2] = blue;

    return pBrick;

}

//------------------------------------------------

void brickplacement(game *game, SDL_Renderer *prenderer, SDL_Window *pwindow)
{
    int count = 0;
    int posY = 50;

    for(int i = 0; i<(*game).brickNumber; i++)
    {
        (*game).bricks[i] = brickGenerator((*game).bricks[i]);

        if((*game).bricks[i] == NULL)
        {
            errorHandeler(prenderer, pwindow, "ERROR when creating a brick");
        }

        if(count >= 7)
        {
            count = 0;
            posY += 50;
        }

        (*(*game).bricks[i]).rectangle.x = (*game).brickGap + (count*((*game).brickGap+(*(*game).bricks[i]).rectangle.w));
        (*(*game).bricks[i]).rectangle.y = posY;

        count++;

    }
  
}



//------------------------------------------------

void clearBrick(pongElement *pBrick)
{
    free(pBrick);
}