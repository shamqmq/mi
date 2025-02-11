#ifndef FILE_HANDLE_H_
#define FILE_HANDLE_H_

#include "include.h"


int copy_file(FILE* to, FILE* from);      //copying files
int fill_lines(FILE* temp_p);             //filling every thing in the file into the line structure
int display_text(LINE* top);              //display the lines structure on the screen
int free_lines(LINE* top);               //free all allocated buffer

#define INPUT_BUFFER 1024 //1024 bytes for the input buffer

#endif // !FILE_HANDLE_H_
