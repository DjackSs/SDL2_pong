#include <SDL.h>
#include <stdio.h>
#include <math.h>

#include "pong.h"
#include "utility.h"




//======================================================
//draw


void cleanRender(SDL_Renderer *prenderer, SDL_Window *pwindow)
{
    if(SDL_SetRenderDrawColor(prenderer, 0, 0, 0, SDL_ALPHA_OPAQUE) != 0)
    {
        errorHandeler(prenderer, pwindow, "ERREUR du changement de la couleurte du rendu");
    }

    SDL_RenderClear(prenderer);

}

//------------------------------------------------

void drawPongElement(pongElement *element, SDL_Renderer *prenderer, SDL_Window *pwindow)
{
    
    if(SDL_SetRenderDrawColor(prenderer, (*element).colorRGB[0], (*element).colorRGB[1], (*element).colorRGB[2], SDL_ALPHA_OPAQUE) != 0)
    {
        errorHandeler(prenderer, pwindow, "ERROR when changing render color");
    }

    if(SDL_RenderFillRect(prenderer, &(*element).rectangle) != 0)
    {
        errorHandeler(prenderer, pwindow, "ERROR while drawing rectangle");
    }

}

//------------------------------------------------

void drawBall(pongBall *ball, SDL_Renderer *prenderer, SDL_Window *pwindow)
{
    if(SDL_SetRenderDrawColor(prenderer, (*ball).colorRGB[0], (*ball).colorRGB[1], (*ball).colorRGB[2], SDL_ALPHA_OPAQUE) != 0)
    {
        errorHandeler(prenderer, pwindow, "ERROR when changing render color");
    }

    for (double i=0; i<=(*ball).radius; i+= (*ball).resolution)
    {
        SDL_FPoint point1;
        SDL_FPoint point2;

        // Pythagore shenanigan
        point1.x = (*ball).center.x + i;
        point1.y = (*ball).center.y + sqrtf(((*ball).radius*(*ball).radius)-((point1.x-(*ball).center.x)*(point1.x-(*ball).center.x)));


        point2.x = (*ball).center.x - i;
        point2.y = (*ball).center.y - sqrtf(((*ball).radius*(*ball).radius)-((point1.x-(*ball).center.x)*(point1.x-(*ball).center.x)));


        if(SDL_RenderDrawLine(prenderer,  point1.x, point1.y , point2.x, point2.y) != 0)
        {
            errorHandeler(prenderer, pwindow, "ERROR drawing a line 1 of the ball");
        }

        if(SDL_RenderDrawLine(prenderer, point2.x, point1.y ,  point1.x, point2.y) != 0)
        {
             errorHandeler(prenderer, pwindow, "ERROR drawing a line 2 of the ball");
        }

    }

}