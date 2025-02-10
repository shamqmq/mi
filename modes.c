#include "modes.h"

int insert_mode(void){
//  chtype cursor_help = inch();
    ch = getch();
    char b = ch;
    getyx(stdscr, y, x);
      switch (ch) {
        case KEY_ENTER:                 //ReTurn button
          insert_buff("\n\0", x, current);
          current = current->next;
          printw("\n\0");
          break;
        case KEY_SPACE:                 //Space button
          insert_buff(" ", x, current);
          printw(" ");
          break;
        case KEY_BACKSPACE:             //Backspace button
          if (x == 0)
            move_left();
          else
          {
            printw("\b \b");
          }
          break;
        case KEY_TAB:                   //Tab button
          insert_buff("\t", x, current);
          printw("\t");
          break;
        case KEY_UP:
          if (move_up() != 0) exit(EXIT_FAILURE);
          break;
        case KEY_DOWN:
          if (move_down() != 0) exit(EXIT_FAILURE);
          break;
        case KEY_LEFT:
          if (move_left() != 0) exit(EXIT_FAILURE);
          break;
        case KEY_RIGHT:
          if (move_right() != 0) exit(EXIT_FAILURE);
          break;
        default:
          insert_buff(&b, x, current);
          printw("%c",ch);
          break;     
     }
    
  
  return EXIT_SUCCESS;
}

int reset_end_ptr(){
  int len = strlen(current->begin);
  current->end = current->handler = current->begin + len;  
  return 0;
}

int move_up(void){
  y--;
  current = current->prev;
  move(y,x);
  return 0;
}
int move_down(void){
  y++;
  current = current->next;
  move(y,x);
  return 0;
}
int move_left(void){
  x--;
  move(y,x);
  return 0;
}
int move_right(void){
  x++;
  move(y,x); 
  return 0;
}

int insert_buff(char* buffer, int x_axis, LINE* current){
  if (current == NULL || current->begin == NULL || current->end == NULL || current->handler == NULL) {
    perror("Invalid LINE structure");
    return -1;
  }
  int size = strlen(buffer); 
  int i;
  current->handler = current->end;
  current->end += size;
  for (i = 0; i < size; i++){
    *(current->end) = *(current->handler);
    current->end--;
    current->handler--;
  }
  current->handler = (current->begin) + x_axis;
  for (i = 0; i < size; i++){
    *buffer = *(current->handler);
    current->handler++;
    buffer++;
  }
  reset_end_ptr();  
  return 0;
}
