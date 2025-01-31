#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <ncurses.h>


// macros

#define KEY_SPACE 32 
#define KEY_TAB 9
#define KEY_ESC 27

// global vars dec 
int x,y;

//funcs declaration

int insert_mode(void);




//main shit
int main(int argc, char *argv[])
{
  // vars declaration
  // init the terminal
  initscr(); 
  noecho();                     // Disapling echoing
  raw();                        // Disapling echo
  cbreak();                     // Disapling the termional line buffering
  keypad(stdscr , TRUE);        // Accepting special char
  insert_mode();

  endwin();
  return EXIT_SUCCESS;
}


int insert_mode(void){
  // vars dec
  int ch;

  while ( ch != KEY_ESC){               //ESC button
//  chtype cursor_help = inch();
    ch = getch();
    getyx(stdscr, y, x);
      switch (ch) {
        case KEY_ENTER:                 //ReTurn button
          printw("\n\0");
          break;
        case KEY_SPACE:                 //Space button
          printw(" ");
          break;
        case KEY_BACKSPACE:             //Backspace button
          /*if (x == 0)*/
          /*{*/
          /*  y--;*/
          /*  move(y,x);*/
          /*  printw("\033[J");*/
          /*}*/
          /*else*/
          printw("\b \b");
          break;
        case KEY_TAB:                   //Tab button
          printw("\t");
          break;
        case KEY_UP:
          y--;
          move(y,x); 
          break;
        case KEY_DOWN:
          y++;
          move(y,x); 
          break;
        case KEY_LEFT:
        /*  if (x == 0)*/
        /*  {*/
        /*    y--;*/
        /*    move(y,x);*/
        /*    printw("\033[J");*/
        /*  }*/
        /**/
        /*else */
          x--;
          move(y,x); 
          break;
        case KEY_RIGHT:
          x++;
          move(y,x); 
          break;
        default:
          printw("%c",ch);
          break;     
      }
    }
  
  return EXIT_SUCCESS;
}
