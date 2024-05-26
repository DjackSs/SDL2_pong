//==========================================
//      PONG
//==========================================


#include <SDL.h>
#include <stdio.h>
#include <string.h>

#include "pong.h"



//------------------------------------------------

void stdin_purge(char *string);

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
       stdin_purge(choice);

        if(choice[0] == '1' || choice[0] == '2')
        {
            pong_sdl_init(choice);
        }

    }
    


    return 0;
}

//------------------------------------------------



void stdin_purge(char *string)
{
    if(string[strlen(string)-1] != '\n')
    {
        int letter = 0;

        while ( letter != '\n' && letter != EOF)
            letter = getchar();

    }

    string[strlen(string)-1] = '\0';


}


