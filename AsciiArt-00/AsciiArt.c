#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>

#include "font.h"

#define KEY_ESC 27

int main(int argc,char *argv[]) {

	int ch;
	int x=1,y=1;
	int rows=0,cols=0;
	int mode=0;
	int pattern='0';

	initscr();
	start_color();

	init_pair(1,COLOR_GREEN,COLOR_BLACK);
	init_pair(2,COLOR_BLACK,COLOR_GREEN);

	cbreak();
	keypad(stdscr,TRUE);
	noecho();

	do {

		attron(COLOR_PAIR(1));
		box(stdscr,0,0);
		attroff(COLOR_PAIR(1));


		move(y,x);

		refresh();

		getmaxyx(stdscr,rows,cols);

		ch=getch();

		switch(ch) {
			case KEY_UP: 	if(y>1)      y--; break;
			case KEY_DOWN: 	if(y<rows-2) y++; break;
			case KEY_LEFT: 	if(x>1)      x--; break;
			case KEY_RIGHT: if(x<cols-2) x++; break;
			case KEY_F(1): mode=0; break;
			case KEY_F(2): mode=1; break;
			case KEY_F(3): mode=2; break;
			case KEY_F(4): mode=3; break;
			default: break;
		}

		switch(mode) {
			case 0:
				if(ch=='\n') {
					x=1;
					if(y<rows-2) y++;
				} else if(ch==KEY_BACKSPACE) {
					if(x>1) x=cols-2;
					else if(y>1) y--;
					mvaddch(y,x,' ');
				} else {
					if(ch>=32 && ch<=255) {
						mvaddch(y,x,ch);
						if(x<cols-1) {
							x++;
						} else {
							x=1;
							if(y<rows-2) y++;
						}
					}
				}
			break;
			case 1:
				if(ch>=0 && ch<=127) {
					attron(COLOR_PAIR(1));
					int k=ch;
					for(int j=0;j<font_height;j++) {
						for(int i=0;i<font_width;i++) {
							int l=font_pixels[i+j*font_width+k*font_height*font_width];
							if(j+y>=1 && j+y<=rows-2 && i+x>=1 && i+x<=cols-2) {
								if(l==0) mvaddch(j+y,i+x,' ');
								else if(l==1) mvaddch(j+y,i+x,pattern);
							}
						}
					}
					attroff(COLOR_PAIR(1));
				}
			break;
			case 2:
				if(ch>=0 && ch<=127) {
					attron(COLOR_PAIR(1));
					int k=ch+128;
					for(int j=0;j<font_height;j++) {
						for(int i=0;i<font_width;i++) {
							int l=font_pixels[i+j*font_width+k*font_height*font_width];
							if(j+y>=1 && j+y<=rows-2 && i+x>=1 && i+x<=cols-2) {
								if(l==0) mvaddch(j+y,i+x,' ');
								else if(l==1) mvaddch(j+y,i+x,pattern);
							}
						}
					}
					attroff(COLOR_PAIR(1));
				}
			break;
			case 3:
				pattern=ch;
			break;
			default: break;
		}

	} while(ch!=KEY_ESC);

	endwin();

	return 0;
}
