#include "modes.h"

// global vars dec 
static int x,y;

static int ch;


int insert_mode(void){

  // vars dec

  while ( ch != KEY_ESC){               //ESC button
    insert_mode_movments();

  }
  return EXIT_SUCCESS;
}

int insert_mode_movments(void){
//  chtype cursor_help = inch();
    ch = getch();
    getyx(stdscr, y, x);
      switch (ch) {
        case KEY_ENTER:                 //ReTurn button
          printw(" \0\n");
          break;
        case KEY_SPACE:                 //Space button
          printw(" ");
          break;
        case KEY_BACKSPACE:             //Backspace button
          if (x == 0)
          {
            y--;
            move(y,x);
          }
          else
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
    
  
  return EXIT_SUCCESS;
}


int insert_buff(char c,BUFF* x_axis, BUFF* y_axis){

}
