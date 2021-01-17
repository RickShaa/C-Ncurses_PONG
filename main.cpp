#include <ncurses.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "graphics.h"
#include "sound.h"
#include "animation.h"
//NCURSES MAIN
static int spalten =0; // number of colums
static int zeilen =0; // number of rows
static int game_state; // dictates the state of the game i.e which screen to show (start, gameloop, endscreen)
char ball[] = "*";
//initilizing counter for player one and two
static int countP1;
static int countP2;
static bool p = 1; // boolean for when you want to exit gameloop and start playing
void init(); // initializes the screen
void gameloop(); // initialises all screens and depending on the state of the game will switch between startscreen, gameloop and endscreen
void start_screen(float t, float dt, int us); // includes while loop for start screen
void pongLoop(float t, float dt, int us); // this is the actuall gameloop where Pong is played
void pause_Screen (float t, float dt, int us); // endscreen loop
void level_screen(float t,float dt, float us);
void p2WinScreen (); // animation for win screen
void p1WinScreen (); // animation for win screen
void playSong();
static bool active1 = false; // dictates which difficulty has been played in order to know when pause is pressed which game state to return to
static bool active2 = false; // dictates which difficulty has been played in order to know when pause is pressed which game state to return to

int main ()
{
    
    init();

    return(0);
}

void init()
{
    // Source: NCurses Tutorial Prof. Dr. Röttger
    initscr();
    curs_set(FALSE);
    noecho();
    
    getmaxyx(stdscr, zeilen, spalten);
    
    clear();
    sound_init();
    start_color();
    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    init_pair(3, COLOR_RED, COLOR_BLACK);
    init_pair(4, COLOR_BLUE, COLOR_BLACK);
    init_pair(5, COLOR_WHITE, COLOR_WHITE);
    
    
    gameloop();
    
    refresh();
    
    sound_exit();
    endwin();
}

void gameloop(){
    
    
    
    int fps = 30;
    float dt = 1.0/fps;
    int us = 1000 * 1000 * dt;
    float t = 0;
    
    timeout(0);
    
    countP1 = 0;
    countP2 = 0;
    
    
    // start screeen will show when starting the game
    start_screen(t, dt, us);
    level_screen(t,dt, us);
    
    /* this is the entire loop. Game state 1 is the win screen for player 1.
     Game state 2 is the win screen for player 2. Game state 3 is the pause/endscreen where the player gets to choose between quiting and starting over.
     game state 4 is the pong loop in easy setting. Game state 5 is the pong loop in medium setting. Game state 6 is when the game is quit. Game state 7 the endscreen*/
    while(p)
    {
        if(game_state == 1)
        {
            p1WinScreen();
            
        }
        else if(game_state == 2)
        {
            
            p2WinScreen();
        }
        else if(game_state == 3)
        {
            
            pause_Screen (t, dt, us);
        }
        
        else if( game_state == 4)
        {
            active1 = true; // indicates was previously active before hitting pause
            pongLoop(t, dt, us);
        }
        else if( game_state == 5)
        {
            active2 = true; // indicates was previously active before hitting pause
            pongLoop(t, dt, us);
        }
        else if(game_state == 6)
        {
            p=0;
            active1 = false;
            active2= false;
        }
        else if(game_state == 7)
        {
            pause_Screen (t, dt, us);
        }
    }
    
    
}

//plays soundtrack
void playSong()
{
    sound_play("sunny.wav");
}


// actual gameplay loop
void pongLoop(float t, float dt, int us)
{
    
    sound_play("win.wav");
    
    
    while(1)
    {
        // initializing offsets for pedal controlls. Pedal one offset = yo, Pedal two offset = yo2 by pressing the controls for up and down offset will increase or decrease
        static int yo = 0;
        static int yo2 = 0;
        
        clear();
        //if screen gets enlarged screen will recalibrate
        getmaxyx(stdscr, zeilen, spalten);
        
        // printing info on how to quit the gameplay
        move(zeilen-2, 2);
        printw("PRESS P TO PAUSE");
        //depending on game state the pedal size will be smaller to make game more difficult
        if(game_state == 4)
        {
            
            animationPedal_OneEasy (yo, zeilen);
            animationPedal_TwoEasy (yo2, spalten, zeilen);
            
        }else
        {
            game_state = 5;
            animationPedal_OneMed (yo,zeilen);
            animationPedal_TwoMed (yo2,spalten, zeilen);
        }
        
        
        
        // adding counter for each player
        attrset(A_BOLD);
        move(1, 2);
        printw("Player One:  %d", countP1);
        move(1, spalten - 15);
        printw("Player Two:  %d", countP2);
        
        
        
        // drawing center line
        char line[] = "|\n|\n|\n|\n|\n|\n|\n|\n|\n|\n|\n|\n|\n|\n|\n|\n|\n|\n|\n|\n|\n|\n|\n";
        
        draw_sprite((zeilen/2) - 12 , spalten/2, line);
        
        
        // draws the plaer animation one and two during the game
        animationP1 (t, dt, zeilen, spalten);
        animationP2 (t,dt, zeilen, spalten);
        
        
        /*starting from here is where the ball animation starts. There is no seperate method because i need the exact location of the ball to identify when to increase the
         counter and stop the game
         */
        attrset(A_NORMAL);
        // initializing start position of the ball
        static float bx = spalten/2;
        static float by = zeilen/4;
        
        
        static float dbx = 30, dby = 30;
        
        color_set(5, NULL);
        // drawing the ball
        draw_sprite(by+0.5,bx+0.5, ball);
        
        
        color_set(1, NULL);
        
        // sets the position of the ball to a different value each frame
        bx += dbx *dt;
        
        by += dby *dt;
        
        
        
        // checks the collision of the ball with screen edge
        //Source: NCurses Tutorial Prof. Dr. Röttger
        if (bx >= spalten-1) dbx = -dbx;
        else if (bx <= 0) dbx = -dbx;
        if (by >= zeilen-1) dby = -dby;
        else if (by <= 0) dby = -dby;
        
        // checks the collision with the pedal Source: NCURSES Tutorial Prof. Dr. Röttger
        int mask = A_CHARTEXT | A_ALTCHARSET;
        
        if (dbx <0)
        {
            int ch = mvinch(by, bx-1) & mask;
            if (ch != ' ' && ch =='*') {
                sound_play("pedal.wav");
                dbx = -dbx;
            }
        }
        else if (dbx > 0)
        {
            int ch = mvinch(by, bx+1) & mask;
            if (ch != ' '&& ch =='*'){
                sound_play("pedal.wav");
                dbx = -dbx;
            }
        }
        
        if (dby <0)
        {
            int ch = mvinch(by-1, bx) & mask;
            if (ch != ' '&& ch =='*') {
                sound_play("pedal.wav");
                dby = -dby;
            }
        }
        if (dby > 0)
        {
            int ch = mvinch(by + 1, bx) & mask;
            if (ch != ' '&& ch =='*')
            {
                sound_play("pedal.wav");
                dby = -dby;
            }
        }
        
        /* checks the position of the ball. If the position bx is smaller or equal to zero count for P2 will increase, ball will be repositioned and the game starts fresh
         with updated score*/
        if ( bx <= 0)
        {
            countP2++;
            
            bx = spalten/2;
            by = zeilen/4;
            refresh();
            sleep(1);
            sound_play("fail.wav");
            
        }
        /* checks the position of the ball. If the position bx is greater or equal to bx-1 count for P1 will increase, ball will be repositioned and the game starts fresh
         with updated score*/
        if( bx>=spalten -1)
        {
            countP1++;
            bx = spalten/2;
            by = zeilen/4;
            sound_play("fail.wav");
            refresh();
            sleep(1);
        }
        //checks total score of each player. If score is higher than 4 game state will change and flip in to win screen
        
        if (countP2 > 4)
        {
            
            game_state = 1;
            break;
        }
        //checks total score of each player. If score is higher than 4 game state will change and flip in to win screen
        if (countP1 > 4)
        {
            
            game_state = 2;
            break;
        }
        
        refresh();
        usleep(us);
        
        t+= dt;
        
        // controls how you can escape the while loop in order to pause the game. When pressing 'p' game state will change to 3
        
        int ch = getch();
        if(ch != EOF)
        {
            if(tolower(ch) == 'p')
            {
                game_state=3;
                break;
            }
            
        }
        // Variationen zum Thema Java: Pong. Controlls the Pedal of each player. Player one is w for up, s for down. Player two is o for up and s for down
        switch (ch)
        {
            case 'w':
                yo-=3;
                break;
            case 's':
                yo+=3;
                break;
            case 'o':
                yo2 -=3;
                break;
            case 'l':
                yo2+=3;
                break;
                
        }
        
        //Switch for score
        //scoreBoard(countP1);
    }
    
}


// screen shows when a player has won. You have the option to quit or play another roung
void p2WinScreen ()
{
    clear();
    
    int x = spalten/2;
    int y = zeilen/2;
    const char text[] = "PRESS Q TO QUIT";
    const char ez[] = "PRESS SPACE TO START A NEW GAME";
    
    
    
    
    int len = strlen(text);
    
    
    
    attrset(A_BOLD);
    
    mvprintw(y +2 , x - len/2,  text);
    mvprintw(y +4 , x - len/2,  ez);
    attrset(A_NORMAL);
    
    attrset(A_BLINK);
    const char player1[]=
    ("######    #      #     # ####### #     #\n"
     "#     #  ##      #  #  # #     # ##    #\n"
     "#     # # #      #  #  # #     # # #   #\n"
     "######    #      #  #  # #     # #  #  #\n"
     "#         #      #  #  # #     # #   # #\n"
     "#         #      #  #  # #     # #    ##\n"
     "#       #####     ## ##  ####### #     # \n");
    
    draw_sprite(y-10, x -20, player1);
    
    //gives you the option to quit
    int ch = getch();
    if(ch != EOF){
        if(tolower(ch) == 'q')
        {
            game_state=7;
        }
        //gives you the option to resume game
        if(tolower(ch) == ' ')
        {
            gameloop();
        }
        
        
    }
    refresh();
    
}


// screen shows when a player has won. You have the option to quit or play another roung

void p1WinScreen ()
{
    
    clear();
    
    int x = spalten/2;
    int y = zeilen/2;
    const char text[] = "PRESS Q TO QUIT";
    const char ez[] = "PRESS SPACE TO START A NEW GAME";
    int len = strlen(text);
    attrset(A_BOLD);
    mvprintw(y +2 , x - len/2,  text);
    mvprintw(y +4 , x - len/2,  ez);
    attrset(A_NORMAL);
    
    
    attrset(A_BLINK);
    const char player2[]=
    ("######   #####     #     # ####### #     #\n"
     "#     # #     #    #  #  # #     # ##    #\n"
     "#     #       #    #  #  # #     # # #   #\n"
     "######   #####     #  #  # #     # #  #  #\n"
     "#       #          #  #  # #     # #   # #\n"
     "#       #          #  #  # #     # #    ##\n"
     "#       #######     ## ##  ####### #     #\n");
    
    draw_sprite(y-10, x -20, player2);
    
    //gives you the option to quit
    int ch = getch();
    if(ch != EOF){
        if(tolower(ch) == 'q'){
            game_state=7;
            
        }
        // gives you the option to start a new game
        if(tolower(ch) == ' ')
        {
            gameloop();
            
        }
        
    }
    
    
    refresh();
    
}




void pause_Screen (float t, float dt, int us)
{
    
    playSong();
    
    // this is the final screen it gives you the option to quit the game or to resume
    
    while(1)
    {
        
        clear();
        getmaxyx(stdscr, zeilen, spalten);
        animationPauseScreen(t, dt, spalten, zeilen, game_state);
        refresh();
        usleep(us);
        
        t+= dt;
        
        //you can quit the pause screen by pressing q
        int ch = getch();
        if(ch != EOF)
        {
            if(tolower(ch) == 'q')
            {
                game_state = 6;
                break;
            }
            /*resumes the game for each individual game mode. The boolean value active1/2 indicates which level had been activated so the programm knows which
             difficulty to return to*/
            if(tolower(ch) == 'c' && active1 == true)
            {
                game_state =4;
                break;
            }
            else if (tolower(ch) == 'c' && active2 == true)
            {
                game_state =5;
                break;
            }
        }
        
        
        
        
    }
    
}



// level screen gives you the option to choose the level of difficulty (size of pedal)
void level_screen(float t,float dt, float us)
{
    
    int x = spalten/2;
    int y = zeilen/2;
    
    while(1)
    {
        
        clear();
        
        getmaxyx(stdscr, zeilen, spalten);
        
        
        const char easy[] = "EASY MODE PRESS 'E'";
        const char med[] = "MEDIUM MODE PRESS 'M'";
        
        int lene = strlen(easy);
        int lenm = strlen(med);
        mvprintw(y , x -lene +2 ,  easy);
        mvprintw(y+2 , x -lenm +4  ,  med);
        
        
        
        refresh();
        usleep(us);
        
        t+= dt;
        // e is easy mode
        int ch = getch();
        if(ch != EOF)
        {
            if(tolower(ch) == 'e')
            {
                game_state = 4;
                break;
                
            }
            
            // m is the more difficult game state
            if(tolower(ch) == 'm')
            {
                game_state = 5;
                break;
            }
            
            
            
            
        }
        
    }
}

void start_screen(float t, float dt, int us){
    
    // intilizes the first screen you see, here is where you are able to start playing the game and see the controls of each player
    
    playSong();
    
    while(1)
    {
        
        clear();
        //falls Fenster vergrößert wir wird die neue größe zum berechnen geholt
        getmaxyx(stdscr, zeilen, spalten);
        
        
        animationStartScreen(t, dt, zeilen, spalten);
        
        
        
        refresh();
        usleep(us);
        
        t+= dt;
        //to start the game press space
        int ch = getch();
        if(ch != EOF)
        {
            if(tolower(ch) == ' ') break;
        }
    }
    
}





