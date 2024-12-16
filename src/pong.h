#ifndef _pong
#define _pong

#include <SDL.h>

//------------------------------------------------

#define DEFAULT_WINDOW_WITH 800
#define DEFAULT_WINDOW_HEIGHT 600

//---------------------
//game board
#define GAME_PADDING 10

enum gameType {BREAKOUT, PONG, EDITOR};

typedef struct game
{
    int width;
    int height;
    int padding;
    int delta;
    int brickNumber;
    int brickGapX;
    int brickGapY;
    enum gameType type;
    char playerNumber;
    int *score;
    struct pongElement **bricks;

} game;

//---------------------
// pong element
#define BRICK_WIDTH 100
#define BRICK_HEIGHT 20
#define BRICK_GAP_Y 40
#define BRICK_RGB_R 215
#define BRICK_RGB_G 24
#define BRICK_RGB_B 202

#define PADDLE_RGB_R 50
#define PADDLE_RGB_G 0
#define PADDLE_RGB_B 115

typedef struct pongElement
{
    struct SDL_Rect rectangle;
    float speed;
    int dirX;
    int dirY;
    int colorRGB[3];

} pongElement;

//---------------------
//ball
#define BALL_RGB_R 0
#define BALL_RGB_G 250
#define BALL_RGB_B 250

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

//game function
void pong_sdl_init(char *choice);

SDL_bool pong_game_init(game *game, pongElement *paddleP1, pongElement *paddleP2, pongBall *ball);

void pong_breakout_game(SDL_Renderer *prenderer, SDL_Window *pwindow);
void pong_pong_game(SDL_Renderer *prenderer, SDL_Window *pwindow);
void pong_editor_game(SDL_Renderer *prenderer, SDL_Window *pwindow);

//controller function
void pong_breakout_controller(SDL_Event event, pongElement *element);
SDL_bool pong_editor_controller(SDL_Event event, pongElement *paddle);
void pong_pong_controller(SDL_Event event, pongElement *paddleP1, pongElement *paddleP2);



#endif