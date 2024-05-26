#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>

#include "pong.h"
#include "draw.h"
#include "control.h"
#include "utility.h"


//======================================================
//main

void pong_sdl_init(char *choice)
{
    
    //---------------------------------------------------------------
    //init SDL

    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
    {
        utility_error_handeler(NULL, NULL, "SDL initialization ERROR");
    }


    //---------------------
    //window

    SDL_Window *pwindow = NULL;

    pwindow = SDL_CreateWindow("Pong", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WITH, WINDOW_HEIGHT, 0);
    if(pwindow == NULL)
    {
        utility_error_handeler(NULL, pwindow, "ERROR creating SDL window");
    }

    //---------------------
    //render

    SDL_Renderer *prenderer = NULL;

    prenderer = SDL_CreateRenderer(pwindow, -1, SDL_RENDERER_ACCELERATED);
    if(prenderer == NULL)
    {
         utility_error_handeler(prenderer, pwindow, "ERROR creating SDL render");
    }

    //---------------------
    // game

    switch(choice[0])
    {
        case '1':
            pong_breakout_game(prenderer, pwindow);
            break;
        case '2':
            pong_pong_game(prenderer, pwindow);
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

void pong_breakout_game(SDL_Renderer *prenderer, SDL_Window *pwindow)
{
    SDL_bool program_launched = SDL_TRUE;
    SDL_Event event;
    Uint64 program_time = SDL_GetTicks64();

    //---------------------
    // game init

    game game;
    pongElement paddle;
    pongBall ball;

    pong_breakout_init(&game, &paddle, &ball);

    utility_brick_placement(&game, prenderer, pwindow);

    //---------------------
    // game Loop

    
    while(program_launched)
    {
        
        if(utility_game_clock(game, &program_time))
        {

            //input
            while(SDL_PollEvent(&event))
            {
                switch(event.type)
                {
                    case SDL_KEYDOWN:
                        pong_breakout_controller(event, &paddle);
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
            control_paddle_out(game, &paddle);
            control_ball_out(&ball, &game);
            control_ball_on_paddle(&ball, game, paddle);
            conotrol_ball_on_brick(&ball, &game);

            //lose
            if(ball.speed <= 0) program_launched = SDL_FALSE;

            //update
            paddle.rectangle.x += (paddle.dirX*paddle.speed);
            ball.center.x += (ball.dirX*ball.speed);
            ball.center.y += (ball.dirY*ball.speed);

            //draw
            draw_clean_render(prenderer, pwindow);
            draw_ball(&ball, prenderer, pwindow);
            draw_pong_element(&paddle, prenderer, pwindow);

            for(int i=0; i<game.brickNumber; i++)
            {
                draw_pong_element(game.bricks[i], prenderer, pwindow);
            }
            

            SDL_RenderPresent(prenderer);
            
        }


     }

    //---------------------
    //game close

    for(int i=0; i<game.brickNumber; i++)
    {
        utility_clear_brick(game.bricks[i]);
    }

    free(game.bricks);

    
}

//------------------------------------------------

void pong_breakout_init(game *game, pongElement *paddle, pongBall *ball)
{
    //game init
    (*game).width = WINDOW_WITH;
    (*game).height = WINDOW_HEIGHT;
    (*game).delta = 5; //ball cross the height in 3 seconds = 600px/3s = 200px/1000ms = 1px/5ms = velocity -> time = 1px/velocity = 5ms
    (*game).brickNumber = 42;
    (*game).brickGap = 12;
    (*game).bricks = NULL;
    (*game).type = 0;
    (*game).score[0] = 0; 


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

void pong_pong_game(SDL_Renderer *prenderer, SDL_Window *pwindow)
{
    SDL_bool program_launched = SDL_TRUE;
    SDL_Event event;
    Uint64 program_time = SDL_GetTicks64();

    //---------------------
    // game init

    game game;
    pongElement paddleP1;
    pongElement paddleP2;
    pongBall ball;

    pong_pong_init(&game, &paddleP1, &paddleP2, &ball);


    //---------------------
    // game Loop

    
    while(program_launched)
    {
    
        if(utility_game_clock(game, &program_time))
        {

            //input
            while(SDL_PollEvent(&event))
            {
                switch(event.type)
                {
                    case SDL_KEYDOWN:
                        pong_pong_controller(event, &paddleP1, &paddleP2);
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
            control_paddle_out(game, &paddleP1);
            control_paddle_out(game, &paddleP2);
            control_ball_out(&ball, &game);
            control_ball_on_paddle(&ball, game, paddleP1);
            control_ball_on_paddle(&ball, game, paddleP2);


            //update
            paddleP1.rectangle.y += (paddleP1.dirY*paddleP1.speed);
            paddleP2.rectangle.y += (paddleP2.dirY*paddleP2.speed);
            ball.center.x += (ball.dirX*ball.speed);
            ball.center.y += (ball.dirY*ball.speed);

            SDL_Delay(game.delta);

            //draw
            draw_clean_render(prenderer, pwindow);
            draw_ball(&ball, prenderer, pwindow);
            draw_pong_element(&paddleP1, prenderer, pwindow);
            draw_pong_element(&paddleP2, prenderer, pwindow);
            

            SDL_RenderPresent(prenderer);
        }

     }

    //---------------------
    //game close


    
}

//------------------------------------------------

void pong_pong_init(game *game, pongElement *paddleP1, pongElement *paddleP2, pongBall *ball)
{
    //game init
    (*game).width = WINDOW_WITH;
    (*game).height = WINDOW_HEIGHT;
    (*game).delta = 5; //ball cross the height in 3 seconds = 600px/3s = 200px/1000ms = 1px/5ms = velocity -> time = 1px/velocity = 5ms
    (*game).brickNumber = 0;
    (*game).type = 1;
    (*game).score[0] = 0;
    (*game).score[1] = 0;


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
    (*ball).radius = 8;
    (*ball).resolution = 1;  //define the shape of the ball, smaller = rounder = more resource intensive. Can't go < 1 pixel.
    (*ball).colorRGB[0] = 0;
    (*ball).colorRGB[1] = 250;
    (*ball).colorRGB[2] = 250;
    (*ball).dirX = 1;
    (*ball).dirY = 0;
    (*ball).speed = 1;

}

//------------------------------------------------

void pong_breakout_controller(SDL_Event event, pongElement *paddle)
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

void pong_pong_controller(SDL_Event event, pongElement *paddleP1, pongElement *paddleP2)
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




