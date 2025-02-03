#ifndef MODES_H_
#define MODES_H_

// macros
#define KEY_SPACE 32 
#define KEY_TAB 9
#define KEY_ESC 27
#define INPUT_BUFFER 1024 //1024 bytes for the input buffer


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <ncurses.h>
#include <limits.h>


int insert_mode_movments(void); 

int insert_mode(void);

void init_queue(Queue* queue);                     // init the queue

void enqueue(Queue *queue , const char * line);    // enqueu 

char* dequeue(Queue *queue);                       // dequeu


int insert_buff(char c,BUFF* x_axis, BUFF* y_axis);





#endif
