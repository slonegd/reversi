#pragma once

//#include <ncurses.h>
#include <ncursesw/ncurses.h>

enum color {
   green = 1, red, blue, black
};

void fillAreaInit()
{
   start_color();
   init_pair (green, COLOR_BLACK, COLOR_GREEN);
   init_pair (red,   COLOR_BLACK, COLOR_RED);
   init_pair (blue,  COLOR_BLACK, COLOR_BLUE);
   init_pair (black, COLOR_BLACK, COLOR_BLACK);
}

void fillArea (color c, int8_t vPos, int8_t hPos)
{
   attron (COLOR_PAIR(c));
      // vPos 0->1 2, 1->4 5, 2->7 8, 3->10 11
      // hPos 0->1, 1->7, 2->13, 3->19
      mvprintw(vPos*2+(vPos+1), hPos*5+(hPos+1), "     ");
      mvprintw(vPos*2+(vPos+2), hPos*5+(hPos+1), "     ");
   attroff (COLOR_PAIR(c));
}