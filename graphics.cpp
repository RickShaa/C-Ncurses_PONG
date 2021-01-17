#include "graphics.h"
#include <ncurses.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>





//Source: NCurses Tutorial Prof. Dr. Röttger
//draws sprite
void draw_sprite(int y , int x, const char *text)
{
    move(y,x);
    while(*text != '\0')
    {
        if (*text == '\n')
        {
            move(++y, x);
        }
        else
        {
            addch(*text);
        }
        
        text++;
        
    }
}
//Source: NCurses Tutorial Prof. Dr. Röttger
//draws line
void draw_line(int x1, int y1, int x2, int y2)
{
    int x = x1;
    int y = y1;
    int dx = x2 -x1;
    int dy = y2- y1;
    int err = dx;
    while(x++ <= x2)
    {
        mvaddch(y,x, '*');
        err -= 2*dy;
        if ( err < 0)
        {
            y++;
            err += 2*dx;
        }
    }
}


//Source: NCurses Tutorial Prof. Dr. Röttger
// prints alt charset
void print_altcharset()
{
    move(3,0);
    color_set(2, NULL);
    attron(A_ALTCHARSET);
    for(int i =32; i<256; i++)
    {
        if(i == 127)
            
        {
            i =160;
        }
        addch(i);
        
    }
    attroff(A_ALTCHARSET);
    color_set(1, NULL);
}
