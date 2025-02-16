#ifndef MODES_H_
#define MODES_H_

#include "include.h"

// macros
#define KEY_SPACE 32 
#define KEY_TAB 9
#define KEY_ESC 27
#define INPUT_BUFFER 1024 //1024 bytes for the input buffer
#define BEGIN 0
#define END 1

// global vars dec 
static int x, y = 0;
static int ch;
static unsigned int lines_count;

typedef struct LINE {
  char* begin;
  char* end;
  char* handler;
  struct LINE* next;
  struct LINE* prev;
} LINE;

static LINE* current = NULL;
static LINE* head = NULL;
static LINE* rear = NULL;

int insert_mode_movments(void);
int insert_mode(void);

int insert_buff(char* buffer,int x_axis, LINE* current);
int delete_buff(int nchar, int x_axis, LINE* cline);
int delete_line(LINE* cline);
void create_node(char* buff, LINE* back, LINE* front);  // buff is buffer inserted back is prev node and front is next node

void redraw_iline(char* buff);
void redraw_dline(int nchar);     // +ve nchar delete back currend (normal), -ve nchar delete forward 
void redraw_text(LINE* top);
// movments
int move_up(void);
int move_down(void);
int move_left(void);
int move_right(void);
void set_edge_curser(int choise);

//resetting the end pointer in the line buffer
int reset_end_ptr();

int display_text(LINE* top);              //display the lines structure on the screen
int is_line_empty(LINE* line);

  // vars dec

#endif
