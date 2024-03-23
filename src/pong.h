#ifndef _pong
#define _pong

#include <SDL.h>

//------------------------------------------------

//game board
typedef struct game
{
    int width;
    int height;
    int clock;
    int brickNumber;
    int brickGap;
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
void sdlInit(char *choice);

void breakoutGame(SDL_Renderer *prenderer, SDL_Window *pwindow);
void breakoutInit(game *game, pongElement *paddle, pongBall *ball);

void pongGame(SDL_Renderer *prenderer, SDL_Window *pwindow);
void pongInit(game *game, pongElement *paddleP1, pongElement *paddleP2, pongBall *ball);

//controller function
void controller(SDL_Event event, pongElement *element);
void pongController(SDL_Event event, pongElement *paddleP1, pongElement *paddleP2);



#endif