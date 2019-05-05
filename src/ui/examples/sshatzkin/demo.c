#include <ncurses.h>
#include <stdio.h>

WINDOW *create_newwin(int height, int width, int starty, int startx);
void destroy_win(WINDOW *local_win);

int main(){
  WINDOW *my_win;
  WINDOW *top_win;
  int startx, starty, width, height;
  int xl,xr,yt,yb; 
  int ch;
  
  initscr();
  cbreak();
  //raw();
  keypad(stdscr,TRUE);
  noecho();
  curs_set(FALSE);

  xl = 0;
  yt = 0;
  
  height = 4;
  width = 8;
  starty = (LINES - height) /2;
  startx = (COLS - width) /2;
  printw("Press F1 to exit");
  refresh();
  
  my_win = create_newwin(height,width,starty,startx);
  
  top_win = create_newwin(6,8,0,0);
  //destroy_win(top_win);
  //top_win = create_newwin(11,5,4,5);
  
  while((ch = getch()) != KEY_F(1)) {
    switch(ch)
      {
      case KEY_LEFT:
	destroy_win(my_win);
	my_win = create_newwin(height, width, starty, --startx);
	break;
      case KEY_RIGHT:
	destroy_win(my_win);
	my_win = create_newwin(height, width, starty, ++startx);
	break;
      case KEY_UP:
	destroy_win(my_win);
	my_win = create_newwin(height, width, --starty, startx);
	break;
      case KEY_DOWN:
	destroy_win(my_win);
	my_win = create_newwin(height, width, ++starty, startx);
	break;
      }
  }
  endwin();
  /*printw("Type any character to see it in bold\n");
  ch = getch();

  if(ch == KEY_F(1))
    printw("F1 Key Pressed");

  else{
    printw("The pressed key is ");
    attron(A_BOLD);
    printw("%c", ch);
    attroff(A_BOLD);
  }
  refresh();
  getch();
  endwin();*/
 

  /*
  curs_set(FALSE);

  sleep(1);

  endwin();
  */
  return 0;
}

WINDOW *create_newwin(int height, int width, int starty, int startx){
  WINDOW *local_win;

  local_win = newwin(height, width, starty, startx);
  box(local_win, 0, 0);

  wrefresh(local_win);

  return local_win;
}

void destroy_win(WINDOW *local_win){
  wborder(local_win, ' ', ' ', ' ', ' ' , ' ', ' ', ' ', ' ');
  wrefresh(local_win);
  delwin(local_win);
}
