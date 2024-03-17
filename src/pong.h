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

//------------------------------------------------

//main function
void breakoutGame(SDL_Renderer *prenderer, SDL_Window *pwindow);
void breakoutInit(game *game, pongElement *paddle, pongBall *ball);

void pongGame(SDL_Renderer *prenderer, SDL_Window *pwindow);
void pongInit(game *game, pongElement *paddleP1, pongElement *paddleP2, pongBall *ball);

//draw function
void cleanRender(SDL_Renderer *prenderer, SDL_Window *pwindow);
void drawBall(pongBall *ball, SDL_Renderer *prenderer, SDL_Window *pwindow);
void drawPongElement(pongElement *element, SDL_Renderer *prenderer, SDL_Window *pwindow);

//control function
void controller(SDL_Event event, pongElement *element);
void pongController(SDL_Event event, pongElement *paddleP1, pongElement *paddleP2);
void paddleOutControl(game game, pongElement *paddle);
void ballGameControl(pongBall *ball, game game);
void ballOnPaddleControl(pongBall *ball, pongElement paddle);
void ballOnBricksControl(pongBall *ball, game game);

//utility function
void errorHandeler(SDL_Renderer *renderer, SDL_Window *window, char *message);
pongElement* brickGenerator(pongElement *pBrick);
void brickplacement(game *game, SDL_Renderer *prenderer, SDL_Window *pwindow);
void clearBrick(pongElement *pBrick);


#endif