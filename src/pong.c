#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include<math.h>

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
/*
        if(((*(*game).bricks[i]).rectangle.x +(*(*game).bricks[i]).rectangle.w) >= (*game).width)
        {
            count = 0;
            posY += 50;

            (*(*game).bricks[i]).rectangle.x = (*game).brickGap + (count*((*game).brickGap+(*(*game).bricks[i]).rectangle.w));
 
        }
*/

        (*(*game).bricks[i]).rectangle.y = posY;

        count++;

    }
  
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

void clearBrick(pongElement *pBrick)
{
    free(pBrick);
}

//======================================================
//control

void controller(SDL_Event event, pongElement *paddle)
{
    switch(event.key.keysym.sym)
    {
        case SDLK_LEFT:
            (*paddle).dirX = -1;
            break;
        case SDLK_RIGHT:
            (*paddle).dirX = 1;
            break;
        default:
            break;
    }

}

//------------------------------------------------

void pongController(SDL_Event event, pongElement *paddleP1, pongElement *paddleP2)
{
    switch(event.key.keysym.sym)
    {
        case SDLK_UP:
            (*paddleP1).dirY = -1;
            break;
        case SDLK_DOWN:
            (*paddleP1).dirY = 1;
            break;
        case SDLK_z:
            (*paddleP2).dirY = -1;
            break;
        case SDLK_s:
            (*paddleP2).dirY = 1;
            break;
        default:
            break;
    }

}

//------------------------------------------------

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
    //lose
    if(((*ball).center.y + (*ball).radius) >= game.height)
    {
        //(*ball).speed = 0;
        (*ball).dirY *= -1;
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

//======================================================
//main

void breakoutGame(SDL_Renderer *prenderer, SDL_Window *pwindow)
{
    SDL_bool program_launched = SDL_TRUE;

    //---------------------
    // game init

    game game;
    pongElement paddle;
    pongBall ball;

    breakoutInit(&game, &paddle, &ball);

    brickplacement(&game, prenderer, pwindow);

    //---------------------
    // game Loop

    
    while(program_launched)
    {
        SDL_Event event;

        //input
        while(SDL_PollEvent(&event))
        {
            switch(event.type)
            {
                case SDL_KEYDOWN:
                    controller(event, &paddle);
                    continue;
                case SDL_KEYUP:
                    paddle.dirX = 0;
                    continue;
                case SDL_QUIT:
                    program_launched = SDL_FALSE;
                    break;
                default:
                    break;
            }

        }

        //control
        paddleOutControl(game, &paddle);
        ballGameControl(&ball, game);
        ballOnPaddleControl(&ball, paddle);
        ballOnBricksControl(&ball, game);

        //update
        paddle.rectangle.x += (paddle.dirX*paddle.speed);
        ball.center.x += (ball.dirX*ball.speed);
        ball.center.y += (ball.dirY*ball.speed);

        SDL_Delay(game.clock);

        //draw
        cleanRender(prenderer, pwindow);
        drawBall(&ball, prenderer, pwindow);
        drawPongElement(&paddle, prenderer, pwindow);

        for(int i=0; i<game.brickNumber; i++)
        {
            drawPongElement(game.bricks[i], prenderer, pwindow);
        }
        

        SDL_RenderPresent(prenderer);

     }

    //---------------------
    //game close

    for(int i=0; i<game.brickNumber; i++)
    {
        clearBrick(game.bricks[i]);
    }

    free(game.bricks);

    
}

//------------------------------------------------

void breakoutInit(game *game, pongElement *paddle, pongBall *ball)
{
    //game init
    (*game).width = 800;
    (*game).height = 600;
    (*game).clock = 5; //ball cross the height in 3 seconds = 600px/3s = 200px/1000ms = 1px/5ms = velocity -> time = 1px/velocity = 5ms
    (*game).brickNumber = 42;
    (*game).brickGap = 12;
    (*game).bricks = NULL;


    (*game).bricks = calloc((*game).brickNumber, sizeof(pongElement*));
    if((*game).bricks == NULL)
    {
        exit(-1);
    }

    //paddle init
    (*paddle).colorRGB[0] = 50;
    (*paddle).colorRGB[1] = 0;
    (*paddle).colorRGB[2] = 115;
    (*paddle).dirX = 0;
    (*paddle).dirY = 0;
    (*paddle).speed = 5;
    (*paddle).rectangle.x = 350;
    (*paddle).rectangle.y = 570;
    (*paddle).rectangle.w = 100;
    (*paddle).rectangle.h = 20;

    //ball init
    (*ball).center.x = 400;
    (*ball).center.y = 400;
    (*ball).radius = 5;
    (*ball).resolution = 0.1; //define the shape of the ball, smaller = rounder = more resource intensive
    (*ball).colorRGB[0] = 0;
    (*ball).colorRGB[1] = 250;
    (*ball).colorRGB[2] = 250;
    (*ball).dirX = 0;
    (*ball).dirY = 1;
    (*ball).speed = 1;

}

//------------------------------------------------

void pongGame(SDL_Renderer *prenderer, SDL_Window *pwindow)
{
    SDL_bool program_launched = SDL_TRUE;

    //---------------------
    // game init

    game game;
    pongElement paddleP1;
    pongElement paddleP2;
    pongBall ball;

    pongInit(&game, &paddleP1, &paddleP2, &ball);


    //---------------------
    // game Loop

    
    while(program_launched)
    {
        SDL_Event event;

        //input
        while(SDL_PollEvent(&event))
        {
            switch(event.type)
            {
                case SDL_KEYDOWN:
                    pongController(event, &paddleP1, &paddleP2);
                    continue;
                case SDL_KEYUP:
                    paddleP1.dirY = 0;
                    paddleP2.dirY = 0;
                    continue;
                case SDL_QUIT:
                    program_launched = SDL_FALSE;
                    break;
                default:
                    break;
            }

        }

        //control
        paddleOutControl(game, &paddleP1);
        paddleOutControl(game, &paddleP2);
        ballGameControl(&ball, game);
        ballOnPaddleControl(&ball, paddleP1);
        ballOnPaddleControl(&ball, paddleP2);


        //update
        paddleP1.rectangle.y += (paddleP1.dirY*paddleP1.speed);
        paddleP2.rectangle.y += (paddleP2.dirY*paddleP2.speed);
        ball.center.x += (ball.dirX*ball.speed);
        ball.center.y += (ball.dirY*ball.speed);

        SDL_Delay(game.clock);

        //draw
        cleanRender(prenderer, pwindow);
        drawBall(&ball, prenderer, pwindow);
        drawPongElement(&paddleP1, prenderer, pwindow);
        drawPongElement(&paddleP2, prenderer, pwindow);
        

        SDL_RenderPresent(prenderer);

     }

    //---------------------
    //game close


    
}

//------------------------------------------------

void pongInit(game *game, pongElement *paddleP1, pongElement *paddleP2, pongBall *ball)
{
    //game init
    (*game).width = 800;
    (*game).height = 600;
    (*game).clock = 5; //ball cross the height in 3 seconds = 600px/3s = 200px/1000ms = 1px/5ms = velocity -> time = 1px/velocity = 5ms



    //paddle init
    (*paddleP1).colorRGB[0] = 50;
    (*paddleP1).colorRGB[1] = 0;
    (*paddleP1).colorRGB[2] = 115;
    (*paddleP1).dirX = 0;
    (*paddleP1).dirY = 0;
    (*paddleP1).speed = 5;
    (*paddleP1).rectangle.x = 10;
    (*paddleP1).rectangle.y = 300;
    (*paddleP1).rectangle.w = 20;
    (*paddleP1).rectangle.h = 100;

    (*paddleP2).colorRGB[0] = 50;
    (*paddleP2).colorRGB[1] = 0;
    (*paddleP2).colorRGB[2] = 115;
    (*paddleP2).dirX = 0;
    (*paddleP2).dirY = 0;
    (*paddleP2).speed = 5;
    (*paddleP2).rectangle.x = 770;
    (*paddleP2).rectangle.y = 300;
    (*paddleP2).rectangle.w = 20;
    (*paddleP2).rectangle.h = 100;

    //ball init
    (*ball).center.x = 400;
    (*ball).center.y = 300;
    (*ball).radius = 5;
    (*ball).resolution = 0.1; //define the shape of the ball, smaller = rounder = more resource intensive
    (*ball).colorRGB[0] = 0;
    (*ball).colorRGB[1] = 250;
    (*ball).colorRGB[2] = 250;
    (*ball).dirX = 1;
    (*ball).dirY = 0;
    (*ball).speed = 1;

}





