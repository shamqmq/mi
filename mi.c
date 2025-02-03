#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <ncurses.h>
#include <limits.h>



#include "modes.h"

// macros
// global vars dec 

//funcs declaration





//main shit

int main(int argc, char *argv[])

{

 // vars declaration
 
  char tempfilename[PATH_MAX];    // tempfile name
  char input[INPUT_BUFFER];       // input buffer

    // if user didnt enter a valid file name or maybe just executed the program without anything else
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);  // simillar to the famous cli commands error msg yk         
        return EXIT_FAILURE;
    }


    // init the terminal

  initscr();
  noecho();                     // Disable echoing
  cbreak();                     // Disable line buffering
  keypad(stdscr, TRUE);         // Accepting special chars
  intrflush(stdscr, FALSE);

    
  snprintf(tempfilename, PATH_MAX, "/tmp/%s.XXXXXX", argv[1]);   // temp file name uses the main filename name in a 6digit pattern sm related to msktemp

    int file_disc = mkstemp(tempfilename);             // Create a tempfile in /tmp

    if (file_disc == -1) {
        perror("Failed to create the file");
        endwin();
        return EXIT_FAILURE;
    }

    FILE *temp_p = fdopen(file_disc, "w+"); // Open the tempfile

    if (temp_p == NULL) {
        perror("Failed to open the file");
        close(file_disc); 
        endwin();
        return EXIT_FAILURE;
    }

    refresh();               // refresh the screen


    insert_mode();                
    fclose(temp_p);
    endwin();
    return EXIT_FAILURE;
}

