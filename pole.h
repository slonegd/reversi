#pragma once

#include <ncursesfunc.h>
#include <player.h>
#include <algorithm>
#include <pseudograph.h>

using namespace std;
using namespace PSEUDO;

template<class color_>
class Pole
{
public:
   Pole(color_ player1color, color_ player2color)
      : pl1ZoneQty(2), pl2ZoneQty(2),
        player { Player<color_>(player1color), Player<color_>(player2color) },
        curPlayer(0)
   {
      // отрисовка границ
      const wstring hor  = Line (6, horisontal());
      const wstring vert = Line (2, vertical());
      const wstring voidHor = Line (6, L' ');

      auto oneLine = [&](auto begin, auto within, auto innerBoard, auto end)
      {
         wstring res = L"";
         res += begin;
         wstring tmpstr = within + innerBoard;
         for (int i = 0; i < 7; ++i)
            res += tmpstr;
         res += within;
         return res += end;
      };

      wstring upBorder    = oneLine ( upLeft(),      hor,     upWithTap(),   upRight() );
      wstring innerVoid   = oneLine ( vertical(),    voidHor, vertical(),    vertical() );
      wstring innerBorder = oneLine ( leftWithTap(), hor,     crossroad(),   rightWithTap() );
      wstring downBorder  = oneLine ( downLeft(),    hor,     downWithTap(), downRight() );

      mvaddwstr (0, 0, upBorder.c_str() );
      for (int i = 1; i < 7 * 3 + 1; i += 3) {
         mvaddwstr (i, 0, innerVoid.c_str() );
         mvaddwstr (i + 1, 0, innerVoid.c_str() );
         mvaddwstr (i + 2, 0, innerBorder.c_str() );
      }
      mvaddwstr (7 * 3 + 1, 0, innerVoid.c_str() );
      mvaddwstr (7 * 3 + 2, 0, innerVoid.c_str() );
      mvaddwstr (7 * 3 + 3, 0, downBorder.c_str() );
      
      // заполнение начальных цветов
      for (int i = 0; i < 8; ++i)
         for (int j = 0; j < 8; ++j)
            pole[i][j] = color_::black;
      pole[3][3] = player[0].col;
      pole[4][4] = player[0].col;
      pole[3][4] = player[1].col;
      pole[4][3] = player[1].col;
      // заливка полей
      for (int i = 0; i < 8; ++i)
         for (int j = 0; j < 8; ++j)
            if ( pole[i][j] != color_::black )
               fillPoleArea (i, j);

      int y,x;
      player[curPlayer].getPosition(y, x);
      fillArea ( blue, y, x );
      mvaddstr(25, 0, "green");
   }


   enum Dir { Up, Down, Left, Right };
   void currentPlayerGo (Dir dir)
   {
      int y,x;
      player[curPlayer].getPosition(y, x);
      fillPoleArea (y, x);
      switch (dir) {
         case Up:    y = (y + 7) % 8; break;
         case Down:  y = (y + 1) % 8; break;
         case Left:  x = (x + 7) % 8; break;
         case Right: x = (x + 1) % 8; break;
      }
      player[curPlayer].setPosition(y, x);
      fillArea (blue, y, x);
      getPoints (y, x);
      move (26, 0);
      printw ("up        %d\n", points.up);
      printw ("down      %d\n", points.down);
      printw ("left      %d\n", points.left);
      printw ("right     %d\n", points.right);
      printw ("upLeft    %d\n", points.upLeft);
      printw ("upRight   %d\n", points.upRight);
      printw ("downRight %d\n", points.downRight);
      printw ("downLeft  %d\n", points.downLeft);
      printw ("all       %d\n", points.all);
   }


   void getMove()
   {
      int y,x;
      player[curPlayer].getPosition(y, x);
      getPoints (y, x);
      if ( points.all != 0 ) {
         fillPoints (y, x);
         changePlayer();
      }
   }



   color_ pole[8][8];
   int pl1ZoneQty;
   int pl2ZoneQty;
   Player<color_> player[2];
   int curPlayer;
   // Points points;


   Player<color_>& otherPlayer()
   {
      int tmp = curPlayer;
      tmp = (tmp + 1) % 2;
      return player[tmp];
   }
   

   Player<color_>& currentPlayer()
   {
      return player[curPlayer];
   }


   void fillPoleArea (int8_t vPos, int8_t hPos)
   {
      fillArea (pole[vPos][hPos], vPos, hPos);
   }


   int getIterator (const int& direction)
   {
      switch ((size_t)&direction - (size_t)&points) {
         case offsetof(Points, up) :        return -8;
         case offsetof(Points, down) :      return  8;
         case offsetof(Points, left) :      return -1;
         case offsetof(Points, right) :     return  1;
         case offsetof(Points, upLeft) :    return -9;
         case offsetof(Points, downRight) : return  9;
         case offsetof(Points, upRight) :   return -7;
         case offsetof(Points, downLeft) :  return  7;
      }
      return 0;
   }


   void changePlayer()
   {
      int y,x;
      player[curPlayer].getPosition(y, x);
      fillPoleArea (y, x);
      curPlayer = (curPlayer + 1) % 2;
      player[curPlayer].getPosition(y, x);
      fillArea (blue, y, x);
      if (player[curPlayer].col == color_::green)
         mvaddstr(25, 0, "green");
      else
         mvaddstr(25, 0, "red  ");
   }


   struct Points {
      union {
         int ar[8];
         struct {
            int up;
            int down;
            int left;
            int right;
            int upLeft;
            int upRight;
            int downRight;
            int downLeft;
         };
      };
      int all;
      void compAll()
      {
         all = 0;
         for (uint8_t i = 0; i < 8; ++i)
            all += ar[i];
      }
   } points;

   void getPoints (int y, int x)
   {
      auto compPointsInDirection = [&] (int& direction)
      {
         direction = 0;
         int iterator = getIterator(direction);
         color_ color;
         for (int i = (x + y*8) + iterator; i >= 0 && i < 64; i += iterator ) {
            color = *((color_*)pole + i);
            if (color == otherPlayer().col) {
               direction++;
            } else if ( (i + iterator) < 0 || (i + iterator) >= 64 ) {
               // до сюда дойдёт только тогда,
               // когда все поля в этом направлении и так наши
               direction = 0;
               break;
            } else if ( color == currentPlayer().col) {
               break;
            } else if (color == color_::black) {
               direction = 0;
               break;
            }
         }
      }; // end []()

      for (uint8_t i = 0; i < 8; ++i)
         if (pole[y][x] == color_::black)
            compPointsInDirection (points.ar[i]);
         else
            points.ar[i] = 0;
      points.compAll();
   }


   void fillPoints (int y, int x)
   {
      auto fillPointsInDirection = [&] (int& direction)
      {
         int iterator = getIterator(direction);
         int i = (x + y*8) + iterator;
         for (int j = 0; j < direction; ++j ) {
            *((color_*)pole + i) = currentPlayer().col;
            i += iterator;
         }
      }; // end []()

      pole[y][x] = currentPlayer().col;
      for (uint8_t i = 0; i < 8; ++i)
         fillPointsInDirection (points.ar[i]);
      // заливка полей
      for (int i = 0; i < 8; ++i)
         for (int j = 0; j < 8; ++j)
            if ( pole[i][j] != color_::black )
               fillPoleArea (i, j);
   }

};