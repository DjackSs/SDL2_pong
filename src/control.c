#include <SDL.h>
#include <stdio.h>

#include "pong.h"

//======================================================
//control

void paddleOutControl(game game, pongElement *paddle)
{
    //horizontal controls
    if((*paddle).rectangle.x - (*paddle).speed <= 0 && (*paddle).dirX == -1)
    {
        (*paddle).dirX = 0;   
    }

    if((*paddle).rectangle.x + (*paddle).rectangle.w + (*paddle).speed >= 800 && (*paddle).dirX == 1)
    {
        (*paddle).dirX = 0;
    }

    //vertical controls
    if((*paddle).rectangle.y - (*paddle).speed <= 0 && (*paddle).dirY == -1)
    {
        (*paddle).dirY = 0;   
    }

    if((*paddle).rectangle.y + (*paddle).rectangle.h + (*paddle).speed >= 600 && (*paddle).dirY == 1)
    {
        (*paddle).dirY = 0;
    }

}

//------------------------------------------------

void ballGameControl(pongBall *ball, game game)
{
    
    if(((*ball).center.y + (*ball).radius) >= game.height)
    {
        //lose in breakout game
        if(game.brickNumber > 0)
        {
            (*ball).speed = 0;
            
        }
        else
        {
            (*ball).dirY *= -1;   
        }  
        
    }

    if(((*ball).center.y - (*ball).radius) <= 0)
    {
        (*ball).dirY *= -1;
    }

    if(((*ball).center.x - (*ball).radius) <= 0)
    {
        (*ball).dirX *= -1;
    }

    if(((*ball).center.x + (*ball).radius) >= game.width)
    {
        (*ball).dirX *= -1;
    }

}

//------------------------------------------------

void ballOnPaddleControl(pongBall *ball, pongElement paddle)
{
    
   if(((*ball).center.y + (*ball).radius) >= paddle.rectangle.y && (((*ball).center.y + (*ball).radius) <= paddle.rectangle.y + paddle.rectangle.h))
   {
        if((*ball).center.x >= paddle.rectangle.x && ( ((*ball).center.x - (*ball).radius) <= (paddle.rectangle.x + paddle.rectangle.w) ))
        {
            if(paddle.rectangle.w > 50)
            {
                (*ball).dirY *= -1;

                (*ball).dirX = paddle.dirX;

            }
            else
            {
                (*ball).dirX *= -1;

                (*ball).dirY = paddle.dirY;

            }
            
        }
   }


}

//------------------------------------------------

void ballOnBricksControl(pongBall *ball, game game)
{
    for(int i=0; i<game.brickNumber; i++)
    {
        if(((*ball).center.y + (*ball).radius) >= (*game.bricks[i]).rectangle.y && ((*ball).center.y - + (*ball).radius) <=  (*game.bricks[i]).rectangle.y +(*game.bricks[i]).rectangle.h)
        {
             if((*ball).center.x >= (*game.bricks[i]).rectangle.x && ( ((*ball).center.x - (*ball).radius) <= ((*game.bricks[i]).rectangle.x + (*game.bricks[i]).rectangle.w) ))
             {
                (*ball).dirY *= -1;

                (*game.bricks[i]).rectangle.x = 0;
                (*game.bricks[i]).rectangle.y = 0;
                (*game.bricks[i]).rectangle.w = 0;
                (*game.bricks[i]).rectangle.h = 0;
             }

        }
    }

}
