/* The SDL hooks for the Super VMW graphics library */

#include <stdio.h>
#include <unistd.h>
#include <ctype.h>
#include "ncurses.h"
#include "svmwgraph.h"
#include <stdlib.h>  /* For atexit() */


typedef struct {
   int  color;
   int  bold;
   char character;
} our_color_t;

our_color_t our_colors[256];

    /* Setup the Graphics */
    /* Pass '0' to auto-detect bpp */
void *curses_setupGraphics(int *xsize,int *ysize,int *bpp, int fullscreen,int verbose)
{
    initscr();
    start_color();
    cbreak();
    noecho();
    nodelay(stdscr,TRUE);
    nonl();  
    keypad(stdscr,TRUE);
    init_pair(0,COLOR_BLACK,COLOR_BLACK);
    init_pair(1,COLOR_BLUE,COLOR_BLACK);
    init_pair(2,COLOR_GREEN,COLOR_BLACK);
    init_pair(3,COLOR_CYAN,COLOR_BLACK);
    init_pair(4,COLOR_RED,COLOR_BLACK);
    init_pair(5,COLOR_MAGENTA,COLOR_BLACK);
    init_pair(6,COLOR_YELLOW,COLOR_BLACK);
    init_pair(7,COLOR_WHITE,COLOR_BLACK);
    init_pair(8,COLOR_BLACK,COLOR_BLACK);
    init_pair(9,COLOR_BLACK,COLOR_BLUE);
    init_pair(10,COLOR_BLACK,COLOR_GREEN);
    init_pair(11,COLOR_BLACK,COLOR_CYAN);
    init_pair(12,COLOR_BLACK,COLOR_RED);
    init_pair(13,COLOR_BLACK,COLOR_MAGENTA);
    init_pair(14,COLOR_BLACK,COLOR_YELLOW);
    init_pair(15,COLOR_BLACK,COLOR_WHITE);
    return NULL;
}



void lookup_color(int r,int g,int b,int i) {


    int bitmask;
   
   if ((r<64) && (g<64) && (b<64)) {
      our_colors[i].color=0;
      our_colors[i].bold=0;
      our_colors[i].character=' ';
      return;
   }
   
   if ((r>64) && (g<64) && (b<64)) {
      our_colors[i].color=12;
      our_colors[i].bold=0;
      our_colors[i].character=' ';
      return;
   }
   if ((g>64) && (r<64) && (b<64)) {
      our_colors[i].color=10;
      our_colors[i].bold=0;
      our_colors[i].character=' ';
      return;
   }
   if ((b>64) && (r<64) && (g<64)) {
      our_colors[i].color=9;
      our_colors[i].bold=0;
      our_colors[i].character=' ';
      return;
   }
   if ((r>64) && (g>64) && (b<64)) {
      our_colors[i].color=14;
      our_colors[i].bold=0;
      our_colors[i].character=' ';
      return;
   }
   if ((r>64) && (b>64) && (g<64)) {
      our_colors[i].color=13;
      our_colors[i].bold=0;
      our_colors[i].character=' ';
      return;
   }
   if ((g>64) && (b>64) && (r<64)) {
      our_colors[i].color=11;
      our_colors[i].bold=0;
      our_colors[i].character=' ';
      return;
   }

   bitmask=0;
   if (r>64) bitmask|=0x4; 
   if (g>64) bitmask|=0x2;
   if (b>64) bitmask|=0x1;
   our_colors[i].color=bitmask;
   if ((r>128) &&
       (g>128) &&
       (b>128)) our_colors[i].bold=1;
   else our_colors[i].bold=0;
   our_colors[i].character='#';
   return;
}
   

void curses_flushPalette(vmwSVMWGraphState *state) {
 
      int i;
      int r,g,b;
   
      for(i=0;i<256;i++) {
	 r=(state->palette[i]>>11)<<3;
         g=((state->palette[i]>>5)&0x3f)<<2;
	 b=(state->palette[i]&0x1f)<<3;
	 
//	 printf("%i %i %i\n",r,g,b);
         lookup_color(r,g,b,i);	 

      }
}


void curses_BlitMem(vmwSVMWGraphState *target_p, vmwVisual *source) {
   
   int x,y,temp_color;
   
   unsigned char *s_pointer;
    
/*   FILE *fff;
   
   fff=fopen("temp.temp","w");
   for (y=0;y<255;y++) {
       fprintf(fff,"%i: %i %i\n",y,our_colors[y].color,our_colors[y].bold);
   }
*/   
   move(0,0);
   for (y=0;y<25;y++) {
       s_pointer=source->memory+(y*8*320);
       for(x=0;x<80;x++) {   
	  //move(y,x);
 
	  temp_color=*(s_pointer);
	  if (our_colors[temp_color].bold)
	     attrset(COLOR_PAIR(our_colors[temp_color].color)|A_BOLD);
	  else 
	     attrset(COLOR_PAIR(our_colors[temp_color].color)|A_NORMAL);
	  addch(our_colors[temp_color].character);
//	  printf("#");
	   s_pointer+=4;
       }
   }
}

void curses_clearKeyboardBuffer() {

//   while(getch()!=ERR) usleep(100);
}

int curses_getInput() {
   
   int ch;
   
   ch=getch();
   if (ch==ERR) return 0;
         
   switch(ch) {
	      case KEY_BACKSPACE: return VMW_BACKSPACE;
	      case 27            : return VMW_ESCAPE;
              case '\n'          : 
              case '\r':
	      case KEY_ENTER     : return VMW_ENTER;
	      case KEY_UP        : return VMW_UP;
	      case KEY_DOWN      : return VMW_DOWN;
	      case KEY_RIGHT     : return VMW_RIGHT;
	      case KEY_LEFT      : return VMW_LEFT;
	      case KEY_F(1)      : return VMW_F1;
	      case KEY_F(2)      : return VMW_F2;
	      case KEY_F(3)	 : return VMW_F3;
	      case KEY_PPAGE     : return VMW_PGUP;
	      case KEY_NPAGE     : return VMW_PGDN;
	      default: return ch;
   }
   return 0;
}

void curses_closeGraphics(void) {
   
   clear();
   refresh();
   nocbreak();
   echo();
   endwin();
}
