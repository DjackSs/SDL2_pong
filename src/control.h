#ifndef _control
#define _control

#include <SDL.h>
#include "pong.h"


//control function
void paddleOutControl(game game, pongElement *paddle);
void ballGameControl(pongBall *ball, game game);
void ballOnPaddleControl(pongBall *ball, pongElement paddle);
void ballOnBricksControl(pongBall *ball, game game);


#endif