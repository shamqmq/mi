#include "modes.h"

int insert_mode(void){
//  chtype cursor_help = inch();
  LINE* temp;
  while ((ch = getch()) != KEY_ESC){
    char b = ch;
    getyx(stdscr, y, x);
    switch (ch) {
      case KEY_ENTER:                 //ReTurn button
        insert_buff("\n\0", x, current);
        current = current->next;
        printw("\n\0");
        move(y+2, 0);
        break;
      case KEY_SPACE:                 //Space button
        redraw_iline(" ");
        break;
      case KEY_BACKSPACE:             //Backspace button
        if (x == 0){
          delete_line(current);
          redraw_text(head);
        }
        else
        {
          redraw_dline(1);
        }
        break;
      case KEY_TAB:                   //Tab button
        redraw_iline("\t");
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
        redraw_iline(&b); 
        break;     
    }
  }
  return 0;
}
int move_up(void){
  if (current != head){
    y--;
    current = current->prev;
    if (x > (int) strlen(current->begin)) set_edge_curser(END);
    move(y, x);
  }
  return 0;
}
int move_down(void){
  if (current != rear){
    y++;
    current = current->next;
    if (x > (int) strlen(current->begin)) set_edge_curser(END);
    move(y, x);
  }
  return 0;
}
int move_left(void){
  x--;
  if (x < 0 && current->prev != NULL){
    move_up();
    set_edge_curser(END);
  }
  else move(y,x);
  return 0;
}
int move_right(void){
  x++;
  if (x > (current->end - current->begin - 2) && current->next != NULL){
    move_down();
    set_edge_curser(BEGIN);
  }
  else if (x < (int) strlen(current->begin)) move(y,x); 
  return 0;
}
int display_text(LINE* top){
  LINE* temp = current;
  int max = getmaxy(stdscr);
  temp = top;
  do {
    if (temp == NULL) break;
    getyx(stdscr, y, x);
    printw("%s", temp->begin? temp->begin : "");
    temp = temp->next;
  } while (max >= y && temp != NULL);
  move(0, 0);
  return 0;
}
void redraw_iline(char* buff){
  insert_buff(buff, x, current);
  mvprintw(y, 0, "%s", current->begin);
  move(y, x + (int) strlen(buff));
}

void redraw_dline(int nchar){
  delete_buff(nchar, x, current);
  mvprintw(y, 0, "%s", current->begin);
  move(y, x - nchar);
}
void redraw_text(LINE* top){
  clear(); 
  display_text(top);
  move(y, 0);
  set_edge_curser(END);
}
// ==================================================================
int insert_buff(char* buffer, int x_axis, LINE* cline) {   //cline = current line
  if (cline == NULL || cline->begin == NULL || cline->end == NULL || cline->handler == NULL) {
    perror("Invalid LINE structure");
    return -1;
  }

  int original_len = (int) strlen(cline->begin);
  if (x_axis < 0 || x_axis > original_len) {
    perror("x_axis out of bounds");
    return -1;
  }

  int size = (int) strlen(buffer);
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
int delete_buff(int nchar, int x_axis, LINE* cline) {
  if (cline == NULL || cline->begin == NULL) {
    return -1;  // Invalid input
  }

  size_t original_len = strlen(cline->begin);
  
  // Validate position and deletion count
  if (x_axis < 0 || x_axis >= (int)original_len || nchar <= 0) {
    return -1;
  }

  // Calculate actual deletable characters
  size_t max_deletable = original_len - x_axis;
  if ((size_t) nchar > max_deletable) {
    nchar = (int) max_deletable;  // Delete only what's available
  }

  // Calculate remaining characters after deletion
  size_t remaining = original_len - x_axis - nchar;

  // Shift characters and null-terminate
  memmove(cline->begin + x_axis -1,
          cline->begin + x_axis + nchar -1,
          remaining + 1);  // +1 to include null terminator

  // Reallocate memory
  size_t new_size = original_len - nchar + 1;
  char* new_begin = realloc(cline->begin, new_size);
  if (!new_begin) {
    return -1;  // Keep original buffer if realloc fails
  }

  // Update pointers
  cline->begin = new_begin;
  cline->begin[new_size - 1] = '\0';  // Explicit null termination
  
  // Update LINE metadata
  cline->handler = cline->begin + x_axis;
  cline->end = cline->begin + new_size - 1;

  return 0;
}
int delete_line(LINE* cline) {
    if (!cline || !head || !rear) return -1;

    // Preserve next node before deletion for iterator safety
    LINE *prev_node = cline->prev;
    LINE *next_node = cline->next;
    

    // Free line content safely
    if (cline->begin) {
        free(cline->begin);
        cline->begin = NULL;
    }

    // Update neighbors' pointers
    if (prev_node) prev_node->next = next_node;
    if (next_node) next_node->prev = prev_node;

    // Update global list pointers
    if (cline == head) head = next_node;
    if (cline == rear) rear = prev_node;

    // Clear and free the node
    memset(cline, 0, sizeof(LINE)); // Prevent stale data
    free(cline);

    // Auto-update current position safely
    if (current == cline) {
        current = next_node ? next_node : prev_node;
        if (!current) current = head; // Fallback to list head
    }

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
      current->handler = current->begin + strlen(current->begin);
      x = (int) strlen(current->begin) -2;   //just for more safty
      if(current == head) x = (int) strlen(current->begin) -1; 
      move(y, x);
      break;
  }   
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

