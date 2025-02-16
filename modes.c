#include "modes.h"

int insert_mode(void){
//  chtype cursor_help = inch();
  LINE* temp;
  while ((ch = getch()) != KEY_ESC){
    char b = ch;
    getyx(stdscr, y, x);
    switch (ch) {
      case KEY_ENTER:                 //ReTurn button
        create_node(" ", current, current->next);
        current = current->next;
        redraw_text(head);
        break;
      case KEY_SPACE:                 //Space button
        redraw_iline(" ");
        break;
      case KEY_BACKSPACE:             //Backspace button
        if (is_line_empty(current)){
          delete_line(current);
          redraw_text(head);
        } else if (x != 0){
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
  else if (x < (int) strlen(current->begin)) move(y,x); 
  return 0;
}
int move_right(void){
  x++;
  if (x > (current->end - current->begin - 1) && current->next != NULL){
    move_down();
    set_edge_curser(BEGIN);
  }
  else if (x < (int) strlen(current->begin)) move(y,x); 
  return 0;
}
int display_text(LINE* top) {
  LINE* temp = top;
  int max_y = getmaxy(stdscr);
  int current_y = 0; 
  erase();
  move(0, 0);
  while (temp != NULL && current_y < max_y) {
    mvprintw(current_y, 0, "%s", temp->begin ? temp->begin : "");
    current_y++;
    temp = temp->next;
  }
  refresh();
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
  move(0, 0);
  initscr(); 
  /*save(temp_p);*/
  display_text(top);
  if (current == head){
    move(0, 0);
    set_edge_curser(BEGIN);
  } else if (current == rear){
    move(y - 1, 0);
    set_edge_curser(END);
  } else {
    move(y, 0);
    set_edge_curser(END);
  }
}
// ==================================================================
int insert_buff(char* buffer, int x_axis, LINE* cline) {   //cline = current line
  if (cline == NULL || cline->begin == NULL || cline->end == NULL || cline->handler == NULL) {
    return -1;
  }

  int original_len = (int) strlen(cline->begin);
  if (x_axis < 0 || x_axis > original_len) {
    return -1;
  }

  int size = (int) strlen(buffer);
  if (size == 0) {
    return 0; // Nothing to insert
  }

  // Reallocate memory for the new string + null terminator
  char *new_begin = realloc(cline->begin, original_len + size + 1);
  if (new_begin == NULL) {
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
    return -1;  
  }

  size_t original_len = strlen(cline->begin);
  if (x_axis < 0 || x_axis >= (int)original_len || nchar <= 0) {
    return -1;
  }
  size_t max_deletable = original_len - x_axis;
  if ((size_t) nchar > max_deletable) {
    nchar = (int) max_deletable;  
  }
  size_t remaining = original_len - x_axis - nchar;
  memmove(cline->begin + x_axis -1,
          cline->begin + x_axis + nchar -1,
          remaining + 1);  
  size_t new_size = original_len - nchar + 1;
  char* new_begin = realloc(cline->begin, new_size);
  cline->begin = new_begin;
  cline->begin[new_size - 1] = '\0';  
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
  if (cline == rear) rear = prev_node;

  // Clear and free the node
  memset(cline, 0, sizeof(LINE)); // Prevent stale data
  free(cline);

  // Auto-update current position safely
  if (current == cline) {
    current = next_node ? next_node : prev_node;
    if (!current) current = head; // Fallback to list head
  }
  
  if (cline == head) head = current = next_node;

  return 0;
}
void create_node(char* buff, LINE* back, LINE* front) {
    LINE* temp = (LINE*)malloc(sizeof(LINE));
    temp->begin = NULL; 
    temp->end = NULL;
    temp->handler = NULL;
    temp->prev = back;
    temp->next = front;
    if (back) back->next = temp;
    if (front) front->prev = temp;
    if (!back && front) front->prev = temp;
    if (!front && back) back->next = temp;
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
      x = (int) strlen(current->begin) -1;   //just for more safty
      if(current == head) x = (int) strlen(current->begin) -1; 
      move(y, x);
      break;
  }   
}
int is_line_empty(LINE* line) {
  if (!line || !line->begin) return 1; // Treat invalid lines as empty
  size_t len = strlen(line->begin);
  return (len == 0) || (len == 1 && line->begin[0] == '\n');
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

void set_head(void){
  LINE* temp;
  temp = current;
  while (temp->prev != NULL) temp->prev;
  head = temp;
}
