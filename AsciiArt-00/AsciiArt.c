#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>

#include "font.h"

#define KEY_ESC 27

int main(int argc,char *argv[]) {

	int ch;
	int x=1,y=1;
	int rows=0,cols=0;

	initscr();
	start_color();

	init_pair(1,COLOR_GREEN,COLOR_BLACK);
	init_pair(2,COLOR_BLACK,COLOR_GREEN);

	cbreak();
	keypad(stdscr,TRUE);
	noecho();

	attron(COLOR_PAIR(1));
	box(stdscr,0,0);
	attroff(COLOR_PAIR(1));

	do {
		move(y,x);

		refresh();

		getmaxyx(stdscr,rows,cols);

		ch=getch();

		if(ch==KEY_UP) 		{ if(y>1) y--;      }
		else if(ch==KEY_DOWN) 	{ if(y<rows-2) y++; }
		else if(ch==KEY_LEFT) 	{ if(x>1) x--;      }
		else if(ch==KEY_RIGHT) 	{ if(x<cols-2) x++; }
		else if(ch>=0 && ch<=127) {
			attron(COLOR_PAIR(1));
			int k=ch;
			for(int j=0;j<font_height;j++) {
				for(int i=0;i<font_width;i++) {
					int l=font_pixels[i+j*font_width+k*font_height*font_width];
					if(j+y>=1 && j+y<=rows-2 && i+x>=1 && i+x<=cols-2) {
						if(l==0) mvaddch(j+y,i+x,' ');
						else if(l==1) mvaddch(j+y,i+x,'X');
					}
				}
			}
			attroff(COLOR_PAIR(1));
		}

	} while(ch!=KEY_ESC);

	endwin();

	return 0;
}
