#include <iostream>
#include <stdint.h>
#include <cstdlib>
#include <ncursesfunc.h>
#include <pole.h>
#include <player.h>

using namespace std;

int main() 
{
   setlocale (LC_ALL, "");
   system("resize -s 40 80");
   initscr();     // Переход в curses-режим
   curs_set(0);   // невидимый курсор
   noecho();      // Не печатать на экране то, что набирает пользователь на клавиатуре
   keypad (stdscr, true);
   fillAreaInit();

   // создать 2 игроков
   // передать Pole в конструктор
   // в поле хранить номер текущего игрока
   // действия на нажатия должны делать игроки
   // соответсвенно currentPlayerGo и getMove в интерфейс
   // в getMove логика ИИ
   Pole<color> pole = Pole<color> (green, red);

   using Dir = Pole<color>::Dir;
   bool game = true;

   while (game) {
      int ch;
      ch = getch();
      switch (ch) {
         case KEY_UP:    pole.currentPlayerGo(Dir::Up);    break;
         case KEY_DOWN:  pole.currentPlayerGo(Dir::Down);  break;
         case KEY_LEFT:  pole.currentPlayerGo(Dir::Left);  break;
         case KEY_RIGHT: pole.currentPlayerGo(Dir::Right); break;
         case KEY_BACKSPACE: game = false;    break;
         case ' ':
            pole.getMove();
            break;
      }
   }

   endwin();   // Выход из curses-режима. Обязательная команда.

   return 0; 
}

