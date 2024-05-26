#include <SDL.h>
#include <stdio.h>
#include <math.h>

#include "pong.h"
#include "utility.h"




//======================================================
//draw


void draw_clean_render(SDL_Renderer *prenderer, SDL_Window *pwindow)
{
    if(SDL_SetRenderDrawColor(prenderer, 0, 0, 0, SDL_ALPHA_OPAQUE) != 0)
    {
        utility_error_handeler(prenderer, pwindow, "ERREUR du changement de la couleurte du rendu");
    }

    SDL_RenderClear(prenderer);

}

//------------------------------------------------

void draw_pong_element(pongElement *element, SDL_Renderer *prenderer, SDL_Window *pwindow)
{
    
    if(SDL_SetRenderDrawColor(prenderer, (*element).colorRGB[0], (*element).colorRGB[1], (*element).colorRGB[2], SDL_ALPHA_OPAQUE) != 0)
    {
        utility_error_handeler(prenderer, pwindow, "ERROR when changing render color");
    }

    if(SDL_RenderFillRect(prenderer, &(*element).rectangle) != 0)
    {
        utility_error_handeler(prenderer, pwindow, "ERROR while drawing rectangle");
    }

}

//------------------------------------------------

void draw_ball(pongBall *ball, SDL_Renderer *prenderer, SDL_Window *pwindow)
{
   
    if(SDL_SetRenderDrawColor(prenderer, (*ball).colorRGB[0], (*ball).colorRGB[1], (*ball).colorRGB[2], SDL_ALPHA_OPAQUE) != 0)
    {
        utility_error_handeler(prenderer, pwindow, "ERROR when changing render color");
    }

    SDL_Rect innerRect;
    
    for (double i=0; i<=(*ball).radius; i+= (*ball).resolution)
    {
        
        // Pythagore shenanigan
        
        innerRect.x = (*ball).center.x - i;

        int yAxisLength = sqrtf(((*ball).radius*(*ball).radius)-((innerRect.x-(*ball).center.x)*(innerRect.x-(*ball).center.x)));
        innerRect.y = (*ball).center.y - yAxisLength;

        innerRect.w = i*2;
        innerRect.h = 2*yAxisLength;

        if(SDL_RenderFillRect(prenderer, &innerRect) != 0)
        {
            utility_error_handeler(prenderer, pwindow, "ERROR while drawing rectangle");
        }


    }

    
}