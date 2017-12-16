#include <iostream>
#include <stdint.h>
#include <cstdlib>
#include <ncursesfunc.h>
#include <pole.h>
#include <player.h>

using namespace std;



bool possible(color player, int8_t vPos, int8_t hPos, color (&pole)[8][8]);

int main() 
{
   initscr();     // Переход в curses-режим
   curs_set(0);   // невидимый курсор
   noecho();      //Не печатать на экране то, что набирает пользователь на клавиатуре
   fillAreaInit();

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

   //Player<color> player_[2] = { Player<color>(green), Player<color>(red) };
   Pole<color> pole_ = Pole<color> (green, red);
   

   color player = green;
   uint8_t plX = 0;
   uint8_t plY = 0;
   
   keypad (stdscr, true);
   using Dir = Pole<color>::Dir;
   bool game = true;
   while (game) {
      int ch;
      ch = getch();
      // fillArea (pole[plY][plX], plY, plX);
      switch (ch) {
         case KEY_UP:    pole_.currentPlayerGo(Dir::Up);    break;
         case KEY_DOWN:  pole_.currentPlayerGo(Dir::Down);  break;
         case KEY_LEFT:  pole_.currentPlayerGo(Dir::Left);  break;
         case KEY_RIGHT: pole_.currentPlayerGo(Dir::Right); break;
         case KEY_BACKSPACE: game = false;    break;
         case ' ':
            pole_.getMove();
            // pole_.changePlayer();
            break;


      }
      // fillArea (blue, plY, plX);
   }

   endwin();   // Выход из curses-режима. Обязательная команда.

   return 0; 
}

bool possible(color player, int8_t vPos, int8_t hPos, color (&pole)[8][8])
{
   int st = 0;
   // up
   // сделать обобщённо
   // если следующий сверху другого цвета+
   // если далее сверху есть свой цвет+
   // перекрасить
   // повторить по всем направлениям
   // если не по одному направлению нет перекрашевания
   // то вернуть false
   /*switch (st) {
      case 0:
         if (pole)
   }
   for (int8_t i = vPos; i != 0; --i) {
      if pole[i] ==
   }*/

   return true;
}