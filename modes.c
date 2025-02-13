#include "modes.h"

int insert_mode(void){
//  chtype cursor_help = inch();
  while ((ch = getch()) != KEY_ESC){
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
        if (move_up() != 0) return(EXIT_FAILURE);
        break;
      case KEY_DOWN:
        if (move_down() != 0) return(EXIT_FAILURE);
        break;
      case KEY_LEFT:
        if (move_left() != 0) return(EXIT_FAILURE);
        break;
      case KEY_RIGHT:
        if (move_right() != 0) return(EXIT_FAILURE);
        break;
      default:
        insert_buff(&b, x, current);
        
        printw("%s",current->begin);
        break;     
    }
  }
  return 0;
}
int move_up(void){
  if (current != head){
    reset_end_ptr();  
    y--;
    if (x > strlen(current->prev->begin)) set_edge_curser(END);
    current = current->prev;
    move(y,x);
  }
  return 0;
}
int move_down(void){
  if (current != rear){
    reset_end_ptr();  
    y++;
    if (x > strlen(current->next->begin)) set_edge_curser(END);
    current = current->next;
    move(y,x);
  }
  return 0;
}
int move_left(void){
  reset_end_ptr();  
  x--;
  if (x < 0 && current->prev != NULL){
    move_up();
    set_edge_curser(END);
  }
  else move(y,x);
  return 0;
}
int move_right(void){
  reset_end_ptr();  
  x++;
  if (x > (current->end - current->begin - 1) && current->next != NULL){
    move_down();
    set_edge_curser(BEGIN);
  }
  else if (x < strlen(current->begin)) move(y,x); 
  return 0;
}
// ==================================================================
int insert_buff(char* buffer, int x_axis, LINE* cline) {   //cline = current line
  if (cline == NULL || cline->begin == NULL || cline->end == NULL || cline->handler == NULL) {
    perror("Invalid LINE structure");
    return -1;
  }

  int original_len = strlen(cline->begin);
  if (x_axis < 0 || x_axis > original_len) {
    perror("x_axis out of bounds");
    return -1;
  }

  int size = strlen(buffer);
  if (size == 0) {
    return 0; // Nothing to insert
  }

  // Reallocate memory for the new string + null terminator
  char *new_begin = realloc(cline->begin, original_len + size + 1);
  if (new_begin == NULL) {
    perror("realloc failed");
    return -1;
  }
  cline->begin = new_begin;


  // Use memmove for safe shifting (handles overlapping regions)
  memmove(cline->begin + x_axis + size, cline->begin + x_axis, original_len - x_axis + 1);
  // Insert the buffer into the created space
  memcpy(cline->begin + x_axis, buffer, size);
  // Update LINE structure pointers
  cline->end = cline->begin + original_len + size;
  cline->handler = cline->begin + x_axis + size; // Adjust handler as needed

  // Ensure the string is null-terminated
  *(cline->end) = '\0';

  return 0;
}
// ==================================================================
void set_edge_curser(int choise){
  switch (choise) {
    case 0:
      current->handler = current->begin;     //just for more safty
      x = 0;
      move(y, x);
      break;
    case 1:
      current->handler = current->end;     //just for more safty
      x = strlen(current->begin);
      move(y, x);
      break;
  }   
}
int reset_end_ptr(){
  int len = strlen(current->begin);
  current->end = current->handler = current->begin + len;  
  return 0;
}

//test functions [will be deleted]
int print_lines(LINE* top){
  printw("\n\n\n\n========================================\n");
  while(top->next != NULL){
    printw("%s", top->begin);
    top = top->next;
  }
  printw("%s\n", top->begin);
  return 0;
}

