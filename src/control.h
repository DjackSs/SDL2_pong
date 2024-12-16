#ifndef _control
#define _control

#include <SDL.h>
#include "pong.h"


//control function
void control_paddle_out(game game, pongElement *paddle);
void control_ball_out(pongBall *ball, game *game);
void control_ball_on_paddle(pongBall *ball, game game, pongElement paddle);
void conotrol_ball_on_brick(pongBall *ball, game *game);
SDL_bool control_brick_on_brick(game game, pongElement brick);


#endif