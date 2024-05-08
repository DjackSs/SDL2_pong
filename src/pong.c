#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>

#include "pong.h"
#include "draw.h"
#include "control.h"
#include "utility.h"


//======================================================
//main

void sdlInit(char *choice)
{
    
    //---------------------------------------------------------------
    //init SDL

    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
    {
        errorHandeler(NULL, NULL, "SDL initialization ERROR");
    }


    //---------------------
    //window

    SDL_Window *pwindow = NULL;

    pwindow = SDL_CreateWindow("Pong", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WITH, WINDOW_HEIGHT, 0);
    if(pwindow == NULL)
    {
        errorHandeler(NULL, pwindow, "ERROR creating SDL window");
    }

    //---------------------
    //render

    SDL_Renderer *prenderer = NULL;

    prenderer = SDL_CreateRenderer(pwindow, -1, SDL_RENDERER_ACCELERATED);
    if(prenderer == NULL)
    {
         errorHandeler(prenderer, pwindow, "ERROR creating SDL render");
    }

    //---------------------
    // game

    switch(choice[0])
    {
        case '1':
            breakoutGame(prenderer, pwindow);
            break;
        case '2':
            pongGame(prenderer, pwindow);
            break;
        default:
            break;
    }
    


    //---------------------
    //close SDL

    SDL_DestroyRenderer(prenderer);
    SDL_DestroyWindow(pwindow);
    SDL_Quit();


}

//------------------------------------------------

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

        //lose
        if(ball.speed <= 0) program_launched = SDL_FALSE;

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
    (*game).width = WINDOW_WITH;
    (*game).height = WINDOW_HEIGHT;
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
    (*ball).radius = 8;
    (*ball).resolution = 1; //define the shape of the ball, smaller = rounder = more resource intensive. Can't go < 1 pixel.
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
    (*game).width = WINDOW_WITH;
    (*game).height = WINDOW_HEIGHT;
    (*game).clock = 5; //ball cross the height in 3 seconds = 600px/3s = 200px/1000ms = 1px/5ms = velocity -> time = 1px/velocity = 5ms
    (*game).brickNumber = 0;


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
    (*ball).resolution = 1;  //define the shape of the ball, smaller = rounder = more resource intensive. Can't go < 1 pixel.
    (*ball).colorRGB[0] = 0;
    (*ball).colorRGB[1] = 250;
    (*ball).colorRGB[2] = 250;
    (*ball).dirX = 1;
    (*ball).dirY = 0;
    (*ball).speed = 1;

}

//------------------------------------------------

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




