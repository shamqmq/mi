#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <string.h>
#include <unistd.h>

// macros

#define MAX_LINES 100
#define MAX_LINE_LENGTH 1024

// Global variables
char content[MAX_LINES][MAX_LINE_LENGTH]; // Buffer to hold text
int lineCount = 0;                        // Number of lines in the buffer
int cursorX = 0, cursorY = 0;             // Cursor position

// funcs declarations

void dis_canon_and_echo(void);  //disable canonical and echo 
void clr_scr(void);             // clear the screen


// the shit
int main(int argc, char *argv[])
{
  dis_canon_and_echo();
  clr_scr();



  return EXIT_SUCCESS;
}

void dis_canon_and_echo(void){
  struct termios term;
  tcgetattr(STDIN_FILENO, &term);                //get the current terminal atterbutes
  term.c_lflag=~( ICANON | ECHO  );              //disabling echo and canonical mode
  tcsetattr(STDIN_FILENO, TCSANOW, &term);       //applying the changes
}

void clr_scr(void) {
    printf("\033[H\033[J"); // ANSI escape code to clear the screen
    fflush(stdout);
}













