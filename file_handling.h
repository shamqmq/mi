#ifndef FILE_HANDLING_H
#define FILE_HANDLING_H


//macros 

#define INPUT_BUFFER 1024 //1024 bytes for the input buffer

//defs

typedef struct {

  char * beg;                          // a ptr to the start of the buffer  
  char * end;                          // a ptr to the start of the end
  char buffer[INPUT_BUFFER];          // a buff of 1024 bytes
  struct LINE* next;                  // ptr to the next node  
}LINE;

typedef struct{

  LINE* front;                            // ptr to the first node in the queue
  LINE*  rear;                             // ptr to the last node in the queue 
}Queue;



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <ncurses.h>
#include <limits.h>


void init_queue(Queue* queue);                     // init the queue

LINE** enqueue(Queue *queue , const char * line);    // enqueu 

char* dequeue(Queue *queue,LINE** line_ptr);  // dequeu
                                              //

