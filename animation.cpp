#include <ncurses.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "graphics.h"
#include "sound.h"



//Pedal for mode: easy lvl
void animationPedal_OneEasy (int yo, int zeilen)
{
    // draws pedal one
    const char pedal1[] = "*\n*\n*\n*\n*\n*\n*\n";
    // variables for the position of the pedal
    static float bx = 2;
    static float by = zeilen/2;
    
    static int posy = by + 0.5;
    static int posx = bx + 0.5;
    color_set(5, NULL);
    // + yo is the offset of the position in order to control it with the keyboard
    draw_sprite(posy + yo,posx, pedal1);
    
    color_set(1, NULL);
    
    
    
}
//pedal for Easy LVL
void animationPedal_TwoEasy (int yo2, int spalten, int zeilen)
{
    // draws pedal two
    const char pedal2[] = "*\n*\n*\n*\n*\n*\n*\n";
    
    
    // variables for the position of the pedal
    static float bx = spalten -2;
    static float by = zeilen/2;
    
    color_set(5, NULL);
    // + yo is the offset of the position in order to control it with the keyboard
    draw_sprite(by+0.5 + yo2,bx+0.5, pedal2);
    
    
    
    color_set(1, NULL);
    
    
}

//pedal for medium LVL
void animationPedal_OneMed (int yo, int zeilen)
{
    const char pedal1[] = "*\n*\n*\n*\n*\n";
    // variables for the position of the pedal
    static float bx = 2;
    static float by = zeilen/2;
    static int posy = by + 0.5;
    static int posx = bx + 0.5;
    
    color_set(5, NULL);
    // + yo is the offset of the position in order to control it with the keyboard
    draw_sprite(posy + yo,posx, pedal1);
    
    
    
    
    color_set(1, NULL);
    
    
    
}
//pedal for medium lvl
void animationPedal_TwoMed (int yo2, int spalten, int zeilen)
{
    // draws pedal two
    const char pedal2[] = "*\n*\n*\n*\n*\n";
    
    
    // variables for the position of the pedal
    static float bx = spalten -2;
    static float by = zeilen/2;
    
    
    
    
    color_set(5, NULL);
    // + yo is the offset of the position in order to control it with the keyboard
    draw_sprite(by+0.5 + yo2,bx+0.5, pedal2);
    
    
    
    color_set(1, NULL);
    
    
}

void animationStartScreen (float t, float dt, int zeilen, int spalten)

{
    int x = spalten/2;
    int y = zeilen/2;
    
    //information for the player
    const char text[] = "PRESS SPACE TO PLAY";
    
    const char line[]="___________________________";
    const char p1[] = "Player 1: UP = W; DOWN = S";
    const char p2[] = "Player 2: UP = O; DOWN = L";
    
    //calculates length of the text for correct positioning
    int len = strlen(text);
    int len2 = strlen(line);
    
    
    mvprintw(zeilen-20 , x -(len2/2)+1,  line);
    mvprintw(zeilen-18 , x -(len2/2)+1 ,  p1);
    mvprintw(zeilen-16 , x -(len2/2)+1 ,  p2);
    
    
    attrset(A_BOLD);
    
    mvprintw(y +2 , x - len/2,  text);
    attrset(A_NORMAL);
    
    //draws the Pong logo
    const char p[] = "******\n*    *\n*    *\n******\n*\n*";
    const char o[] = "******\n*    *\n*    *\n*    *\n*    *\n******";
    const char n[] = "**     *\n* *    *\n*  *   *\n*   *  *\n*    * *\n*     **";
    const char g[] = "******\n*\n*\n*  ***\n*    *\n******\n";
    
    //position for logo
    static int bx = spalten/2;
    static int by = zeilen/4;
    
    // offset to move the logo
    static int dbx = 1, dby = 0;
    
    //Color animation
    static int colorCode = 1;
    if(colorCode >=2){
        colorCode = 1;
        color_set(colorCode, NULL);
    } else {
        colorCode++;
    }
    color_set(colorCode, NULL);
    //draws the actual text
    draw_sprite(by-1,bx, p);
    draw_sprite(by-1,bx + 8 , o);
    draw_sprite(by-1,bx + 16 , n);
    draw_sprite(by-1,bx +26, g);
    //mvaddch(by, bx, '*');
    color_set(1, NULL);
    
    //moves object
    bx += dbx;
    by += dby;
    
    //checks collision with window screen
    if (bx >= spalten-32) dbx = -dbx;
    else if (bx <= 0) dbx = -dbx;
}

void animationP1 (float t, float dt, int zeilen, int spalten){
    
    int bx = spalten/2 - 25;
    int y = 2;
    
    attrset(A_BLINK);
    const char player1[]=
    
    ("####    #\n"
     "#   #  ##\n"
     "#   # # #\n"
     "####    #\n"
     "#       #\n"
     "#      ###\n");
    
    draw_sprite(y, bx, player1);
}

void animationP2 (float t, float dt, int zeilen, int spalten){
    
    int bx = spalten/2 + 15;
    int y = 2;
    
    attrset(A_BLINK);
    const char player1[]=
    
    ("####   #####\n"
     "#   #      #\n"
     "#   #  #####\n"
     "####  #     \n"
     "#     ######\n"
     "#           \n");
    
    draw_sprite(y, bx, player1);
}

// this is the end and pause screen, when game state = 3 you can resume the game, if game state is anything else but three this is the end screen
void animationPauseScreen(float t, float dt, int spalten, int zeilen, int game_state)
{
    // tells you how to quit or resume the game
    int x = spalten/2;
    int y = zeilen/2;
    const char text[] = "PRESS Q TO EXIT GAME";
    const char es[] = "CONTINUE PRESS 'C'";
    const char thx[] = "THANKS FOR PLAYING PONG";
    const char pause[]= "PAUSE";
    int len = strlen(text);
    int len2 = strlen(es);
    attrset(A_BOLD);
    mvprintw(y +2 , x - len/2,  text);
    
    /* if this screen is shown when you press pause during the game it will display "PRESS Q TO EXIT GAME" and "CONTINUE PRESS C" if it is shown as an exit screen it
     it will replace continue with "THANKS FOR PLAYING PONG*/
    if(game_state == 3)
    {
        mvprintw(y +4 , x - len/2,  es);
        attrset(A_BLINK);
        color_set(3, NULL);
        mvprintw(y-10 , x -3,  pause);
        
    }else
    {
        mvprintw(y +4 , x - len/2,  thx);
    }
    attrset(A_NORMAL);
    
}
