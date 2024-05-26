#ifndef _pong
#define _pong

#include <SDL.h>

//------------------------------------------------

//game board
typedef struct game
{
    int width;
    int height;
    int delta;
    int brickNumber;
    int brickGap;
    char type; // 0 = breakout, 1 = pong
    int score[2];
    struct pongElement **bricks;

} game;

// pong element
typedef struct pongElement
{
    struct SDL_Rect rectangle;
    float speed;
    int dirX;
    int dirY;
    int colorRGB[3];

} pongElement;

//ball
typedef struct pongBall
{
    struct SDL_Point center;
    int radius;
    float speed;
    int dirX;
    int dirY;
    int colorRGB[3];
    float resolution;

} pongBall;

#define WINDOW_WITH 800
#define WINDOW_HEIGHT 600

//------------------------------------------------

//main function
void pong_sdl_init(char *choice);

void pong_breakout_init(game *game, pongElement *paddle, pongBall *ball);
void pong_breakout_game(SDL_Renderer *prenderer, SDL_Window *pwindow);

void pong_pong_init(game *game, pongElement *paddleP1, pongElement *paddleP2, pongBall *ball);
void pong_pong_game(SDL_Renderer *prenderer, SDL_Window *pwindow);


//controller function
void pong_breakout_controller(SDL_Event event, pongElement *element);
void pong_pong_controller(SDL_Event event, pongElement *paddleP1, pongElement *paddleP2);



#endif