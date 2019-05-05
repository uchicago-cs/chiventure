#include <ncurses.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>


/* bomb
 * Ends the current ncurses session in the case of an error in memory allocation
 *
 *Inputs: N/A
 *
 * Returns: N/A
 */
void bomb(void)
{
  addstr("Unable to allocate memory for new window.\n");
  refresh();
  endwin();
  exit(1);
}

/*create_newwin
 * Creates a windo with the specified dimensions and location
 * 
 * Inputs:
 *  - height: height of the window
 *  - width : width of the window
 *  - starty : initial vertical position of the window
 *  - startx : initial horizontal position of the window
 *  - show : indicates whether or not to draw a box around the window.
 * 
 * Returns: 
 *  - A pointer to the new window
 */
WINDOW *create_newwin(int height, int width, int starty, int startx, int show){
  WINDOW *local_win;

  //initialize new window and throw error if allocation fails
  if( (local_win = newwin(height, width, starty, startx)) == NULL) bomb();

  //If show = true, add window border
  if (show){
    box(local_win, 0, 0);
    wrefresh(local_win);
  }

  return local_win;
}

int *maxx, *maxy, *halfx, *halfy;
/*Recalculate dims
 * When called, recalculates max height, width and half heights and widths
 *
 *Inputs: N/A
 * 
 *Returns:
 * - (Sets maxx*, maxy*, halfx*, and halfy*)
 */
int recalc_dims(){
  getmaxyx(stdscr, *maxy, *maxx);
  *halfx = *maxx >> 1;
  *halfy = *maxy >> 1;
  return 1;
}


int main()
{
  //Initialize variables
  WINDOW *top_bar, *text_box, *c, *d;
  char command[100];
  //  int maxx, maxy, halfx, halfy;
  int height_txt,height_bar;
  int ch,x,y;
  int char_count = 0;
  int score = 22000;
  int line = 1;
  maxx = malloc(sizeof(int));
  maxy = malloc(sizeof(int));
  halfx = malloc(sizeof(int));
  halfy = malloc(sizeof(int));
  //Initialize ncurses screen
  initscr();
  noecho();
  refresh();

  //Initialize colors
  start_color();
  init_pair(1, COLOR_BLACK, COLOR_BLUE);
  init_pair(2, COLOR_BLACK, COLOR_RED);
  init_pair(3, COLOR_BLACK, COLOR_GREEN);
  init_pair(4, COLOR_BLACK, COLOR_CYAN);
  init_pair(5, COLOR_GREEN, COLOR_BLACK);

  /* calculate window sizes and locations
   initialize variables that store window dimensions*/
  //  getmaxyx(stdscr, maxy, maxx);
  //*halfx = *maxx >> 1;
  //*halfy = *maxy >> 1;
  recalc_dims();
  height_txt = *halfy;
  height_bar = 2;
  
  /* create four windows to fill the screen */
  top_bar = create_newwin(height_bar, *maxx, 0, 0, 0);
  text_box = create_newwin(height_txt, *maxx, *halfy, 0, 1);

  //Wait for key presses in text_box
  keypad(text_box, TRUE);
  //Prints '>' in the bottom window
  mvwprintw(text_box, line, 2, ">");

  //Prints Score to top window
  mvwprintw(top_bar, 1, 2, "Score: %i", score);
  
  //  if( (top_bar = newwin(2, maxx, 0, 0)) == NULL) bomb();
  //  if( (text_box = newwin(halfy, maxx, halfy+1, 0)) == NULL) bomb();
  if( (c = newwin(*halfy, *halfx, *halfy, 0)) == NULL) bomb();
  if( (d = newwin(*halfy, *halfx, *halfy, *halfx)) == NULL) bomb();

  //Set top bar background
  wbkgd(top_bar, COLOR_PAIR(4));
  wrefresh(top_bar);

  //Set text_box background & colors
  wbkgd(text_box, COLOR_PAIR(5));
  wrefresh(text_box);
  
  /* Write to each window */
  //mvwaddstr(top_bar, 0, 0, " Chiventure                   Score: 8\n");
  //wrefresh(top_bar);

  /* Give input that will be printed in the text box*/
  // wscanw(text_box,"%s",command);
  //wrefresh(text_box);

  //mvwaddstr(b, 0, 0, "This is window B\n");
  //wbkgd(b, COLOR_PAIR(2));
  //wrefresh(b);
  //  mvwaddstr(c, 0, 0, "This is window C\n");
  //wbkgd(c, COLOR_PAIR(3));
  //wrefresh(c);
  //mvwaddstr(d, 0, 0, "This is window D\n");
  //wbkgd(d, COLOR_PAIR(4));

  //Game Loop _________________________________________________
  while((ch = wgetch(text_box)) !=KEY_F(1)){
    //height = LINES /2;
    //width = COLS;

    recalc_dims();
    
    wclear(top_bar);
    wresize(top_bar,2,*maxx);
    wresize(text_box, *halfx, *maxx);
    mvwin(text_box, *halfy, 0);

    if(isalnum(ch) || ch == ' '){
      winsch(text_box, ch);
      char_count++;

      getyx(text_box,y,x);
      wmove(text_box,y,x+1);
    }


  }
  
  /* Print command string in window4*/
  wprintw(d,"%s",command);
  wrefresh(d);
  getch();
  endwin();
  return 0;
}

