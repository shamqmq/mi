#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <ncurses.h>




//funcs declaration

int insert_mode(void);




//main shit
int main(int argc, char *argv[])
{
  // vars declaration

  // init the terminal
  initscr(); 
  noecho();                     // Disapling echoing
  raw(); );                     // Disapling echo
  cbreak();                     // Disapling the termional line buffering
  keypad(stdscr , TRUE);        // Accepting special char
  insert_mode();

  endwin();
  return EXIT_SUCCESS;
}


int insert_mode(void){
  // vars dec
  char ch;


  while ((int) ch != 27){       //ESC button
    ch = getch();
    switch ((int) ch) {
      case 13:                 //ReTurn button
        printw("\n\0");
        break;
      case 32:                 //Space button
        printw(" ");
        break;
      case 127:               //Backspace button
        printw("\b \b");
        break;
      case 9:                 //Tab button
        printw("\t");
        break;
      default:
        printw("%c",ch);
        break;     
    }
  }
  return EXIT_SUCCESS;
}
