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
  noecho();
  raw();
  cbreak();
  insert_mode();

    endwin();
  return EXIT_SUCCESS;
}


int insert_mode(void){
  // vars dec
  char ch;


  while ((int) ch != 27){
    ch = getch();
    switch ((int) ch) {
      case 13:
        printw("\n\0");
        break;
      case 32:
        printw(" ");
        break;
      case 127:
        printw("\b \b");
        break;
      case 9:
        printw("\t");
        break;
      default:
        printw("%c",ch);
        break;     
    }
  }
  return EXIT_SUCCESS;
}
