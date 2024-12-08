#ifndef _pong
#define _pong

#include <SDL.h>

//------------------------------------------------

#define DEFAULT_WINDOW_WITH 800
#define DEFAULT_WINDOW_HEIGHT 600

#define GAME_PADDING 10

#define BRICK_WIDTH 100
#define BRICK_HEIGHT 20
#define BRICK_GAP_Y 50
#define BRICK_RGB_R 215
#define BRICK_RGB_G 24
#define BRICK_RGB_B 202

#define PADDLE_RGB_R 50
#define PADDLE_RGB_G 0
#define PADDLE_RGB_B 115

#define BALL_RGB_R 0
#define BALL_RGB_G 250
#define BALL_RGB_B 250

//game board
typedef struct game
{
    int width;
    int height;
    int padding;
    int delta;
    int brickNumber;
    int brickGapX;
    int brickGapY;
    char type; // 0 = breakout, 1 = pong
    char playerNumber;
    int *score;
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
void pong_sdl_init(char *choice);

SDL_bool pong_breakout_init(game *game, pongElement *paddle, pongBall *ball);
void pong_breakout_game(SDL_Renderer *prenderer, SDL_Window *pwindow);

SDL_bool pong_pong_init(game *game, pongElement *paddleP1, pongElement *paddleP2, pongBall *ball);
void pong_pong_game(SDL_Renderer *prenderer, SDL_Window *pwindow);


//controller function
void pong_breakout_controller(SDL_Event event, pongElement *element);
void pong_pong_controller(SDL_Event event, pongElement *paddleP1, pongElement *paddleP2);



#endif