#include <ncurses.h>
#include <stdlib.h>

void bomb(void);

int main(int argc, char *argv[])
{
  WINDOW *top_bar, *text_box, *c, *d;
  char command[100];
  int maxx, maxy, halfx, halfy;

  initscr();
  refresh();
  start_color();
  init_pair(1, COLOR_BLACK, COLOR_BLUE);
  init_pair(2, COLOR_BLACK, COLOR_RED);
  init_pair(3, COLOR_BLACK, COLOR_GREEN);
  init_pair(4, COLOR_BLACK, COLOR_CYAN);
  init_pair(5, COLOR_GREEN, COLOR_BLACK);
  /* calculate window sizes and locations */
  getmaxyx(stdscr, maxy, maxx);
  halfx = maxx >> 1;
  halfy = maxy >> 1;
  /* create four windows to fill the screen */
  if( (top_bar = newwin(2, maxx, 0, 0)) == NULL) bomb();
  if( (text_box = newwin(halfy, maxx, halfy+1, 0)) == NULL) bomb();
  if( (c = newwin(halfy, halfx, halfy, 0)) == NULL) bomb();
  if( (d = newwin(halfy, halfx, halfy, halfx)) == NULL) bomb();
  wbkgd(top_bar, COLOR_PAIR(4));
  wrefresh(top_bar);
  //box(text_box,'a','b');
  //refresh();
  wbkgd(text_box, COLOR_PAIR(3));
  wrefresh(text_box);
  
  /* Write to each window */
  mvwaddstr(top_bar, 0, 0, " Chiventure                   Score: 8\n");
  wrefresh(top_bar);

  /* Give some input that will be printed on window 4*/
  wscanw(text_box,"%s",command);
  wrefresh(text_box);
  //mvwaddstr(b, 0, 0, "This is window B\n");
  //wbkgd(b, COLOR_PAIR(2));
  //wrefresh(b);
  mvwaddstr(c, 0, 0, "This is window C\n");
  wbkgd(c, COLOR_PAIR(3));
  wrefresh(c);
  mvwaddstr(d, 0, 0, "This is window D\n");
  wbkgd(d, COLOR_PAIR(4));

  /* Print command string in window4*/
  wprintw(d,"%s",command);
  wrefresh(d);
  getch();
  endwin();
  return 0;
}

void bomb(void)
{
  addstr("Unable to allocate memory for new window.\n");
  refresh();
  endwin();
  exit(1);
}  
