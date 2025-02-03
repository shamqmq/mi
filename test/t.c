#include <ncurses.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>


#define KEY_SPACE 32 
#define KEY_TAB 9
#define KEY_ESC 27


int main(int argc, char *argv[])
{
  int ch;
  int x,y;


  initscr();
  noecho();
  raw();
  cbreak();
  keypad(stdscr, TRUE);
  while (ch != 27) {
    ch = getch();
    getyx(stdscr, y, x);
      switch (ch) {
        case KEY_UP:
          y--;
          move(y,x); 
          break;
        case KEY_DOWN:
          y++;
          move(y,x); 
          break;
        case KEY_LEFT:
          x--;
          move(y,x); 
          break;
        case KEY_RIGHT:
          x++;
          move(y,x); 
          break;
        case KEY_ENTER:                 //ReTurn button
          printw("\n\0");
          break;
        case KEY_SPACE:                 //Space button
          printw(" ");
          break;
        case KEY_BACKSPACE:               //Backspace button
          printw("\b \b");
          break;
        case KEY_TAB:                 //Tab button
          printw("\t");
          break;
        default:
          printw("%c",ch);
          break;     
      }
    refresh();
    }




  endwin();
  return EXIT_SUCCESS;
}
