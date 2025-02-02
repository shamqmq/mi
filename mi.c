#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <ncurses.h>
#include <limits.h>


// macros

#define KEY_SPACE 32 
#define KEY_TAB 9
#define KEY_ESC 27
#define INPUT_BUFFER 1024           //1024 bytes for the input buffer

// global vars dec 
int x,y;

//funcs declaration

int insert_mode(void);




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
    //insert_mode();                

    
    snprintf(tempfilename, PATH_MAX, "/tmp/%s.XXXXXX", argv[1]);   // temp file name uses the main filename name in a 6digit pattern sm related to msktemp

    int file_disc = mkstemp(tempfilename);             // Create a tempfile in /tmp

    if (file_disc == -1) {
        perror("Failed to create the file");
        endwin();
        return EXIT_FAILURE;
    }

    FILE *temp_p = fdopen(file_disc, "w"); // Open the tempfile

    if (temp_p == NULL) {
        perror("Failed to open the file");
        close(file_disc); 
        endwin();
        return EXIT_FAILURE;
    }

    refresh();               // refresh the screen


    fclose(temp_p);
    endwin();
    return EXIT_FAILURE;
}

int insert_mode(void){
  // vars dec
  int ch;

  while ( ch != KEY_ESC){               //ESC button
//  chtype cursor_help = inch();
    ch = getch();
    getyx(stdscr, y, x);
      switch (ch) {
        case KEY_ENTER:                 //ReTurn button
          printw("\n\0");
          break;
        case KEY_SPACE:                 //Space button
          printw(" ");
          break;
        case KEY_BACKSPACE:             //Backspace button
          /*if (x == 0)*/
          /*{*/
          /*  y--;*/
          /*  move(y,x);*/
          /*  printw("\033[J");*/
          /*}*/
          /*else*/
          printw("\b \b");
          break;
        case KEY_TAB:                   //Tab button
          printw("\t");
          break;
        case KEY_UP:
          y--;
          move(y,x); 
          break;
        case KEY_DOWN:
          y++;
          move(y,x); 
          break;
        case KEY_LEFT:
        /*  if (x == 0)*/
        /*  {*/
        /*    y--;*/
        /*    move(y,x);*/
        /*    printw("\033[J");*/
        /*  }*/
        /**/
        /*else */
          x--;
          move(y,x); 
          break;
        case KEY_RIGHT:
          x++;
          move(y,x); 
          break;
        default:
          printw("%c",ch);
          break;     
      }
    }
  
  return EXIT_SUCCESS;
}
