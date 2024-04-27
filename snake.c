#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include <unistd.h>

// constant
#define WIDTH 20
#define HEIGHT 20

// default value for int global variable is 0
int gameover;
// default value for int global variable is 0
int x, y, fruitX, fruitY, score;
// define the tail length with array, the default value of each array index is 0
int tailX[100], tailY[100];
// variable for current tail length
int nTail = 0;
// enum for direction
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
// dir is variable with eDirection data type
enum eDirection dir;

void Setup()
{
    initscr();
    clear();
    // enable keypad mode to capture special keys
    keypad(stdscr, TRUE); 
    // turns off echoing of characters typed by the user. the charatecter typed by user will not show on the screen
    noecho();
    // disables line buffering and allows the program to receive input character by character.
    cbreak();
    // hide the cursor
    curs_set(0);

    gameover = 0;
    dir = STOP;
    x = WIDTH / 2;
    y = HEIGHT / 2;

    fruitX = rand() % WIDTH;
    if (fruitX == 0) fruitX = 1;

    fruitY = rand() % HEIGHT;
    if (fruitY == 0) fruitY = 1;

    score = 0;
}

void Draw()
{
    // clear terminal screen
    clear();

    // draw top border
    for (int i = 0; i < WIDTH + 2; i++)
        mvprintw(0, i, "-");
    // draw bottom border
    for (int i = 0; i < WIDTH + 2; i++)
        mvprintw(HEIGHT + 1, i, "-");
    // draw left border
    for (int i = 0; i < HEIGHT + 2; i++)
        mvprintw(i, 0, "|");
    // draw right border    
    for (int i = 0; i < HEIGHT + 2; i++)
        mvprintw(i, WIDTH + 1, "|");

    // draw a snake head
    mvprintw(y, x, "*");
    // draw snake tail
    for (int i = 0; i < nTail; i++){
         mvprintw(tailY[i] , tailX[i] , "*");
    }

    // draw fruit
    mvprintw(fruitY, fruitX, "*");

    // draw score
    mvprintw(HEIGHT + 3, 0, "Score: %d", score);

    // refresh terminal screen
    refresh();
}

void Input()
{
    //delay in ms
    timeout(300);
    //  it captures a single character of input from the user
    // getch() waits for user input, but if no input is received within timeout duration / timeout(int), it returns timout and doesn't fulfill switch case condition
    int c = getch();
    switch(c)
    {
        case KEY_LEFT:
            dir = LEFT;
            break;
        case KEY_RIGHT:
            dir = RIGHT;
            break;
        case KEY_UP:
            dir = UP;
            break;
        case KEY_DOWN:
            dir = DOWN;
            break;
        case 'x':
            gameover = 1;
            break;
    }
}

void Logic()
{
    // store the value of tailX[0] and tailY[0] to variable prevX and prevY accordingly
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    // assigne the value of x and y to tailX[0] and tailY[0] accordingly, x and y value before being added or subtracted
    tailX[0] = x;
    tailY[0] = y;
    // assign tailX with array index more than 0, and assign tailY with array index more than 0
    // the for looping is kind of shifting value from tailX[0] and tailY[0] until tailX[nTail - 1] and tailY[nTail - 1] accordingly
    for (int i = 1; i < nTail; i++)
    {
        // store the value of tailX[i] and tailY[i] to variable prev2X and prev2Y accordingly
        prev2X = tailX[i];
        prev2Y = tailY[i];
        // assign the value prevX and prevY to tailX[i] and tailY[i], it is like shifting value from tailX[0] until tailX[nTail - 1]
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }
    // the screen coordinate of top left screen is (x=0, y=0)
    // pressing arrow left button will cause the x coordinate to be subtracted by one
    // pressing arrow right button will cause the x coordinate to be added by one
    switch (dir)
    {
        case LEFT:
            x--;
            break;
        case RIGHT:
            x++;
            break;
        case UP:
            y--;
            break;
        case DOWN:
            y++;
            break;
        default:
            break;
    }
    // check condition if the snake hit the left border or right border
    if (x >= WIDTH + 1) x = 1; else if (x < 1) x = WIDTH + 1;
    // check condition if the snake hit the top border or bottom border
    if (y >= HEIGHT + 1) y = 1; else if (y < 1) y = HEIGHT + 1;

    // check condition if the snake head hit the tail
    for (int i = 0; i < nTail; i++)
        if (tailX[i] == x && tailY[i] == y)
            gameover = 1;

    // check condition if the snake head hit the fruit or not 
    if (x == fruitX && y == fruitY)
    {
        score += 10;
        fruitX = rand() % WIDTH;
        if (fruitX == 0) fruitX = 1;

        fruitY = rand() % HEIGHT;
        if (fruitY == 0) fruitY = 1;

        nTail++;
    }
}

// sudo apt-get install libncurses5-dev
// gcc -o snake snake.c -lncurses
int main()
{
    Setup();
    while (!gameover)
    {
        Draw();
        Input();
        Logic();
    }
    endwin();
    return 0;
}
