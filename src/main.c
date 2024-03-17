//==========================================
//      PONG
//==========================================


#include <SDL.h>
#include <stdio.h>
#include <string.h>

#include "pong.h"

#define WINDOW_WITH 800
#define WINDOW_HEIGHT 600

//------------------------------------------------

void sdlInit(char *choice);
void purge (char *string);

//------------------------------------------------

int main (int argc , char * *argv)
{

    char choice[3] = {0};

    while(choice[0] != '3')
    {
        printf("====================\n");
        printf("\t HELLO\n");
        printf("====================\n");
        printf("Choose your game: \n");
        printf("1 - Breakout\n");
        printf("2 - Pong\n");
        printf("3 - Exit\n");

       fgets(choice, 3, stdin);
       purge(choice);

        if(choice[0] == '1' || choice[0] == '2')
        {
            sdlInit(choice);
        }

    }
    


    return 0;
}

//------------------------------------------------

void sdlInit(char *choice)
{
    
    //---------------------------------------------------------------
    //init SDL

    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
    {
        errorHandeler(NULL, NULL, "SDL initialization ERROR");
    }


    //---------------------
    //WINDOW

    SDL_Window *pwindow = NULL;

    pwindow = SDL_CreateWindow("Pong", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WITH, WINDOW_HEIGHT, 0);
    if(pwindow == NULL)
    {
        errorHandeler(NULL, pwindow, "ERROR creating SDL window");
    }

    //---------------------
    //RENDERER

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

void purge (char *string)
{
    if(string[strlen(string)-1] != '\n')
    {
        int letter = 0;

        while ( letter != '\n' && letter != EOF)
            letter = getchar();

    }

    string[strlen(string)-1] = '\0';


}


