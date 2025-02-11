#include "file_handle.h"


int copy_file(FILE* to, FILE* from){
  char stream[INPUT_BUFFER];     //input_bufffer = 1024
  // Validate file pointers
    if (to == NULL || from == NULL) {
        perror("Invalid file pointer");
        return -1;
    }

    // Copy data from 'from' to 'to'
    while (fgets(stream, sizeof(stream), from) != NULL) {
        if (fputs(stream, to) == EOF) {
            perror("Error writing to output file");
            return -1;
        }
    }

    // Check for read errors
    if (ferror(from)) {
        perror("Error reading from input file");
        return -1;
    }

    // Flush the output stream to ensure all data is written
    if (fflush(to) == EOF) {
        perror("Error flushing output file");
        return -1;
    }
  return 0;
}
int fill_lines(FILE* temp_p) {
  char stream[INPUT_BUFFER] = {0}; // Local buffer for reading lines
  LINE* temp = NULL;

  // Allocate memory for the head node
  head = (LINE*)malloc(sizeof(LINE));
  if (head == NULL) {
    perror("Failed to allocate memory for head");
    return -1;
  }
    
  fseek(temp_p, 0, SEEK_SET);         // reset the file pointer the top of the file  
    
  // Read the first line
  if (fgets(stream, sizeof(stream), temp_p) == NULL) {
    perror("Failed to read from file and fill the LINEs");
    free(head); // Free the head node if reading fails
    return -1;
  }

  // Allocate memory for the first line's buffer
  head->begin = (char*)malloc((strlen(stream) + 1) * sizeof(char));
  if (head->begin == NULL) {
    perror("Failed to allocate memory for head->begin");
    free(head); // Free the head node if allocation fails
    return -1;
    }

  // Copy the line into the allocated buffer
  strcpy(head->begin, stream);
  head->end = head->handler = head->begin + strlen(head->begin);
  head->prev = NULL;
  head->next = NULL;
  temp = head;
  lines_count = 1;

  while (fgets(stream, sizeof(stream), temp_p) != NULL) {
  current = (LINE*)malloc(sizeof(LINE));
    if (current == NULL) {
      perror("Failed to allocate memory for current");
      return -1;
    }

    current->begin = (char*)malloc((strlen(stream) + 1) * sizeof(char));
    if (current->begin == NULL) {
      perror("Failed to allocate memory for current->begin");
      free(current); // Free the current node if allocation fails
      return -1;
    }

    // Copy the line into the allocated buffer
    strcpy(current->begin, stream);
    current->end = current->handler = current->begin + strlen(current->begin);
    current->prev = temp;
    current->next = NULL;

    // Link the previous node to the current node
    temp->next = current;
    temp = current;
    lines_count++;
  }

  rear = current; 
  current = head; 
  return 0;
}

int display_text(LINE* top){
  int max = getmaxy(stdscr);
  do {
    getyx(stdscr, y, x);
    printw("%s", current->begin);
    current = current->next;
  } while (max >= y && current != NULL);
  return 0;
}

int free_lines(LINE* top){
  current = top;
  LINE* next;
  while (current != NULL) {
    next = current->next; // Save the next node

    // Free the buffer allocated for 'begin'
    if (current->begin != NULL) {
      free(current->begin);
      current->begin = NULL; // Avoid dangling pointers
    }

    // Free the current node
    free(current);
    current = NULL; // Avoid dangling pointers

    // Move to the next node
    current = next;
  }
  return 0;
}
