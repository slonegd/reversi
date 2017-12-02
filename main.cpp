#include <iostream>
#include <stdint.h>
#include <cstdlib>
#include <ncurses.h>

using namespace std;

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

int main() 
{
	initscr();      // Переход в curses-режим
	curs_set(0);    // невидимый курсор

	printw ("-------------------------------------------------\n");
	printw ("|     |     |     |     |     |     |     |     |\n");
	printw ("|     |     |     |     |     |     |     |     |\n");
	printw ("|-----|-----|-----|-----|-----|-----|-----|-----|\n");
	printw ("|     |     |     |     |     |     |     |     |\n");
	printw ("|     |     |     |     |     |     |     |     |\n");
	printw ("|-----|-----|-----|-----|-----|-----|-----|-----|\n");
	printw ("|     |     |     |     |     |     |     |     |\n");
	printw ("|     |     |     |     |     |     |     |     |\n");
	printw ("|-----|-----|-----|-----|-----|-----|-----|-----|\n");
	printw ("|     |     |     |     |     |     |     |     |\n");
	printw ("|     |     |     |     |     |     |     |     |\n");
	printw ("|-----|-----|-----|-----|-----|-----|-----|-----|\n");
	printw ("|     |     |     |     |     |     |     |     |\n");
	printw ("|     |     |     |     |     |     |     |     |\n");
	printw ("|-----|-----|-----|-----|-----|-----|-----|-----|\n");
	printw ("|     |     |     |     |     |     |     |     |\n");
	printw ("|     |     |     |     |     |     |     |     |\n");
	printw ("|-----|-----|-----|-----|-----|-----|-----|-----|\n");
	printw ("|     |     |     |     |     |     |     |     |\n");
	printw ("|     |     |     |     |     |     |     |     |\n");
	printw ("|-----|-----|-----|-----|-----|-----|-----|-----|\n");
	printw ("|     |     |     |     |     |     |     |     |\n");
	printw ("|     |     |     |     |     |     |     |     |\n");
	printw ("-------------------------------------------------\n");


   color pole[8][8] = {
      {black, black, black, black, black, black, black, black}, 
      {black, black, black, black, black, black, black, black}, 
      {black, black, black, black, black, black, black, black}, 
      {black, black, black, red,   green, black, black, black}, 
      {black, black, black, green, red,   black, black, black}, 
      {black, black, black, black, black, black, black, black}, 
      {black, black, black, black, black, black, black, black}, 
      {black, black, black, black, black, black, black, black}
   };

	fillAreaInit();
	fillArea (red,   3, 3);
	fillArea (red,   4, 4);
	fillArea (green, 3, 4);
	fillArea (green, 4, 3);
   uint8_t plX = 0;
   uint8_t plY = 0;
   fillArea (blue, plY, plX);
   
   keypad (stdscr, true);

   bool game = true;
   while (game) {
      int ch;
      ch = getch();
      fillArea (pole[plY][plX], plY, plX);
      switch (ch) {
         case KEY_UP:    plY = (plY + 7) % 8; break;
         case KEY_DOWN:  plY = (plY + 1) % 8; break;
         case KEY_LEFT:  plX = (plX + 7) % 8; break;
         case KEY_RIGHT: plX = (plX + 1) % 8; break;
         case KEY_BACKSPACE: game = false;    break;
      }
      fillArea (blue, plY, plX);
   }

	endwin();       // Выход из curses-режима. Обязательная команда.

	return 0; 
}