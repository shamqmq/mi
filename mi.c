#include "modes.c"
#include "file_handle.c"
// global vars dec 

//main shit

int main(int argc, char *argv[]){    
  // vars declaration
   
  char tempfilename[PATH_MAX];    // tempfile name
  int file_disc;
  FILE *temp_p; 
  FILE *main_p;


    // if user didnt enter a valid file name or maybe just executed the program without anything else
  if (argc < 2) {
    fprintf(stderr, "Usage: %s <filename>\n", argv[0]);  // simillar to the famous cli commands error msg yk         
    return EXIT_FAILURE;
  }

    
  snprintf(tempfilename, PATH_MAX, "/tmp/%s.XXXXXX", argv[1]);   // temp file name uses the main filename name in a 6digit pattern sm related to msktemp

  file_disc = mkstemp(tempfilename);             // Create a tempfile in /tmp

  if (file_disc == -1) {
    perror("Failed to create the file");
    return EXIT_FAILURE;
  }

  temp_p = fdopen(file_disc, "w+"); // Open the tempfile
  
  if (temp_p == NULL) {
    perror("Failed to open the temp file");
    close(file_disc); 
    return EXIT_FAILURE;
  }
  
  main_p = fopen(argv[1],"r+"); // openning the main file to copy from it 
  if ( main_p == NULL ) {
    perror("Failed to open the file");
    close(file_disc); 
    return EXIT_FAILURE;
  }

  // TODO: test the usr saving or not and do it    
  
  if ( copy_file(temp_p, main_p) != 0){
    perror("Failed to copy file to the temp");
    close(file_disc);
    fclose(temp_p);
    fclose(main_p);
    return EXIT_FAILURE;
  }
  if ( fill_lines(temp_p) != 0){
    perror("Failed to fill the lines");
    close(file_disc);
    fclose(temp_p);
    fclose(main_p);
    return EXIT_FAILURE;
  }

  // init the terminal

  initscr();
  noecho();                     // Disable echoing
  cbreak();                     // Disable line buffering
  keypad(stdscr, TRUE);         // Accepting special chars
  intrflush(stdscr, FALSE);
  if ( display_text(head) != 0){
    perror("Failed to display the text on the screen");
    close(file_disc);
    fclose(temp_p);
    fclose(main_p);
    return EXIT_FAILURE;
  }
  
  refresh();               // refresh the screen

  
  if ( insert_mode() != 0){
    perror("Failed to enter the isert mode");
    close(file_disc);
    return EXIT_FAILURE;
  }
  if (free_lines(head) != 0){
    perror("Falid to free the lines from the heap run nigga run");
    close(file_disc);
    fclose(temp_p);
    fclose(main_p);
    return EXIT_FAILURE;
  }
  fclose(temp_p);
  fclose(main_p);
  close(file_disc);
  getchar();
  endwin();
  return EXIT_SUCCESS;
}

