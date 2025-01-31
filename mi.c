#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <ncurses.h>


// macros

#define KEY_SPACE 32 
#define KEY_TAB 9
#define KEY_ESC 27



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


  while ( ch != KEY_ESC){       //ESC button
    ch = getch();
      switch (ch) {
        case KEY_UP:
          printw(" UP ");
          break;
        case KEY_DOWN:
          printw(" DOWN ");
          break;
        case KEY_LEFT:
          printw(" LEFT ");
          break;
        case KEY_RIGHT:
          printw(" RIGHT ");
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
    }
  
  return EXIT_SUCCESS;
}
