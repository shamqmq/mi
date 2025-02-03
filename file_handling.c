#include "file_handling.h"


typedef struct {

  char * beg;                          // a ptr to the start of the buffer  
  char * end;                          // a ptr to the start of the end
  struct LINE* next;                  // ptr to the next node  
}LINE;

typedef struct{

  LINE* front;                            // ptr to the first node in the queue
  LINE*  rear;                             // ptr to the last node in the queue 
}Queue; 



// init the queue

void init_queue(Queue *queue) {
   queue->front = queue->rear = NULL;                      // empties both the start and the end 

}


// when a user types we add each line to the queue

LINE** enqueue(Queue *queue , const char * line) {
    
  LINE * new_line = (LINE*) malloc(sizeof(LINE));         // allocating memory for the new NODE
                                                          
  strncpy(new_line->next, line , INPUT_BUFFER);    // cp the line to the buffer

  new_line->next = NULL;                             // init the next line
  
  if (queue->rear == NULL) {
      
    // if queue's empty then both front and end ptrs should initially point to the new line
    queue->front = queue->rear = new_line;
  }

  else {

      // if the queue's not empty then append to queue

      queue->rear->next = next ;                 // append to the end of the queue's next line the new line 
       queue->rear = next;                            // point to the last line
  }


  LINE** line_ptr = &new_line;                  // a ptr to the new_line

  return line_ptr;

}
 
// dequeing the Queue and then return a line form it

char* dequeue(Queue *queue , LINE** line_ptr) {

  // if the queue's front ptr not pointing to anything then its empty ; do nothing

  if (queue->front == NULL) {
    
    printf("nothing to do..."); 
    return NULL;           
  }

  LINE* temp = queue->front;                            // temp ptr to hold front's data so we wont loose the data after updating the front ptr 
  
  char * line = temp->buffer;                      // get the data from the temp front node 

  queue->front = queue->front->next;               // move forward

  // if queue becomes empty after that then reset the queue (make front = end = NULL)

  if(queue->front==NULL) {

    queue->rear = NULL; 
  }

  temp = *line_ptr->next;                 

  free(*line_ptr);                          // free the ptr to the new line
  
  line_ptr = temp->next;                    // go to next line
 
  free(temp);                               // free the old front node after updating it

  

  return line;
}

