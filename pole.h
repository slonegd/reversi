#pragma once

#include <ncursesfunc.h>
#include <player.h>
#include <algorithm>

template<class color_>
class Pole
{
public:
   Pole(color_ player1color, color_ player2color)
      : pl1ZoneQty(2), pl2ZoneQty(2),
        player { Player<color_>(player1color), Player<color_>(player2color) },
        curPlayer(0)
   {
      for (int i = 0; i < 8; ++i)
         for (int j = 0; j < 8; ++j)
            pole[i][j] = color_::black;
      pole[3][3] = player[0].col;
      pole[4][4] = player[0].col;
      pole[3][4] = player[1].col;
      pole[4][3] = player[1].col;
      for (int i = 0; i < 8; ++i)
         for (int j = 0; j < 8; ++j)
            if ( pole[i][j] != color_::black )
               fillPoleArea (i, j);
      int y,x;
      player[curPlayer].getPosition(y, x);
      fillArea ( blue, y, x );
      mvaddstr(30, 0, "green");
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
      move (31, 0);
      printw ("up        %d\n", points.up);
      printw ("down      %d\n", points.down);
      printw ("left      %d\n", points.left);
      printw ("right     %d\n", points.right);
      printw ("upLeft    %d\n", points.upLeft);
      printw ("upRight   %d\n", points.upRight);
      printw ("downRight %d\n", points.downRight);
      printw ("downLeft  %d\n", points.downLeft);
   }


   void changePlayer()
   {
      int y,x;
      player[curPlayer].getPosition(y, x);
      pole[y][x] = player[curPlayer].col;
      fillPoleArea (y, x);
      curPlayer = ++curPlayer % 2;
      player[curPlayer].getPosition(y, x);
      fillArea (blue, y, x);
      if (player[curPlayer].col == color_::green)
         mvaddstr(30, 0, "green");
      else
         mvaddstr(30, 0, "red  ");
   }

   void getMove()
   {
      int y,x;
      int st = 0;
      player[curPlayer].getPosition(y, x);
      if ( getPoint (Up, y, x) )
         changePlayer();
   }

   int getPoint(Dir dir, int y, int x)
   {
      //Up
      int point = 0;
      int tmp = 0;
      for (int i = y - 1; i >= 0; --i) {
         int tmp2 = get1point (i, x, i == 0);
         if (tmp2 == -2) {
            tmp = 0;
            break;
         } else if (tmp2 == -1) {
            break;
         } else {
            tmp += tmp2;
         }
      }
      if (tmp) {
         for (int i = y - 1; i >= 0 && pole[i][x] == otherPlayer().col; --i) {
            pole[i][x] = currentPlayer().col;
            fillPoleArea(i,x);
         }
      }
      point += tmp;
      // down
      tmp = 0;
      for (int i = y + 1; i <= 7; ++i) {
         int tmp2 = get1point (i, x, i == 7);
         if (tmp2 == -2) {
            tmp = 0;
            break;
         } else if (tmp2 == -1) {
            break;
         } else {
            tmp += tmp2;
         }
      }
      if (tmp) {
         for (int i = y + 1; i >= 0 && pole[i][x] == otherPlayer().col; ++i) {
            pole[i][x] = currentPlayer().col;
            fillPoleArea(i,x);
         }
      }
      point += tmp;
      // left
      tmp = 0;
      for (int i = x - 1; i >= 0; --i) {
         int tmp2 = get1point (y, i, i == 0);
         if (tmp2 == -2) {
            tmp = 0;
            break;
         } else if (tmp2 == -1) {
            break;
         } else {
            tmp += tmp2;
         }
      }
      if (tmp) {
         for (int i = x - 1; i >= 0 && pole[y][i] == otherPlayer().col; --i) {
            pole[y][i] = currentPlayer().col;
            fillPoleArea(y,i);
         }
      }
      point += tmp;
      // right
      tmp = 0;
      for (int i = x + 1; i <= 7; ++i) {
         int tmp2 = get1point (y, i, i == 7);
         if (tmp2 == -2) {
            tmp = 0;
            break;
         } else if (tmp2 == -1) {
            break;
         } else {
            tmp += tmp2;
         }
      }
      if (tmp) {
         for (int i = x + 1; i <= 7 && pole[y][i] == otherPlayer().col; ++i) {
            pole[y][i] = currentPlayer().col;
            fillPoleArea(y,i);
         }
      }
      point += tmp;

      // up-left
      tmp = 0;
      int j = x - 1;
      for (int i = y - 1; i >= 0 && j >= 0; --i) {
         int tmp2 = get1point (i, j, i == 0 || j == 0);
         if (tmp2 == -2) {
            tmp = 0;
            break;
         } else if (tmp2 == -1) {
            break;
         } else {
            tmp += tmp2;
         }
         --j;
      }
      if (tmp) {
         j = x - 1;
         for (int i = y - 1; i >= 0 && pole[i][j] == otherPlayer().col; --i) {
            pole[i][j] = currentPlayer().col;
            fillPoleArea(i,j);
            --j;
         }
      }
      point += tmp;

      // up-right
      tmp = 0;
      j = x + 1;
      for (int i = y - 1; i >= 0 && j <= 7; --i) {
         int tmp2 = get1point (i, j, i == 0 || j == 7);
         if (tmp2 == -2) {
            tmp = 0;
            break;
         } else if (tmp2 == -1) {
            break;
         } else {
            tmp += tmp2;
         }
         ++j;
      }
      if (tmp) {
         j = x + 1;
         for (int i = y - 1; i >= 0 && pole[i][j] == otherPlayer().col; --i) {
            pole[i][j] = currentPlayer().col;
            fillPoleArea(i,j);
            ++j;
         }
      }
      point += tmp;

      // down-right
      tmp = 0;
      j = x + 1;
      for (int i = y + 1; i <= 7 && j <= 7; ++i) {
         int tmp2 = get1point (i, j, i == 7 || j == 7);
         if (tmp2 == -2) {
            tmp = 0;
            break;
         } else if (tmp2 == -1) {
            break;
         } else {
            tmp += tmp2;
         }
         ++j;
      }
      if (tmp) {
         j = x + 1;
         for (int i = y + 1; i <= 7 && pole[i][j] == otherPlayer().col; ++i) {
            pole[i][j] = currentPlayer().col;
            fillPoleArea(i,j);
            ++j;
         }
      }
      point += tmp;
      
      // down-left
      tmp = 0;
      j = x - 1;
      for (int i = y + 1; i <= 7 && j >= 0; ++i) {
         int tmp2 = get1point (i, j, i == 7 || j == 0);
         if (tmp2 == -2) {
            tmp = 0;
            break;
         } else if (tmp2 == -1) {
            break;
         } else {
            tmp += tmp2;
         }
         --j;
      }
      if (tmp) {
         j = x - 1;
         for (int i = y + 1; i <= 7 && pole[i][j] == otherPlayer().col; ++i) {
            pole[i][j] = currentPlayer().col;
            fillPoleArea(i,j);
            --j;
         }
      }
      point += tmp;   

      return point;
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
   };

   void getPoints (int y, int x)
   {
      int dX;
      int dY;
      int qty;

      auto compPointsInDirection = [&] (int& direction)
      {
         direction = 0;
         int iterator;
         color_ color;
         switch ((size_t)&direction - (size_t)&points) {
            case offsetof(Points, up) :        iterator = -8; break;
            case offsetof(Points, down) :      iterator = 8;  break;
            case offsetof(Points, left) :      iterator = -1; break;
            case offsetof(Points, right) :     iterator = 1;  break;
            case offsetof(Points, upLeft) :    iterator = -9; break;
            case offsetof(Points, downRight) : iterator = 9;  break;
            case offsetof(Points, upRight) :   iterator = -7;  break;
            case offsetof(Points, downLeft) :  iterator = 7; break;
         }

         for (int i = (x + y*8) + iterator; i >= 0 && i < 64; i += iterator ) {
            color = *((color_*)pole + i);
            if ( color == currentPlayer().col)
               break;
            else if (color == otherPlayer().col)
               direction++;
            else if (color == color_::black) {
               direction = 0;
               break;
            } else if ( i == 0 || i == 7 ) {
               // до сюда дойдёт только тогда,
               // когда все поля в этом направлении и так наши
               direction = 0;
               break;
            }
         }
      };
      compPointsInDirection (points.up);
      compPointsInDirection (points.down);
      compPointsInDirection (points.left);
      compPointsInDirection (points.right);
      compPointsInDirection (points.upLeft);
      compPointsInDirection (points.upRight);
      compPointsInDirection (points.downLeft);
      compPointsInDirection (points.downRight);
   }



   // 1 +1 очко
   // -1 дошли до противника, засчитать очки, перестать считать
   // -2 не дошли до противника, все очки обнулить
   int get1point (int y, int x, bool breakCond)
   {
      int tmp = 0;
      if (breakCond && otherPlayer().col != pole[y][x]) {
         tmp = -2;
      } else if (otherPlayer().col == pole[y][x])
         tmp = 1;
      else if (currentPlayer().col == pole[y][x])
         tmp = -1;
      else if (currentPlayer().col == color_::black)
         tmp = -2;
      return tmp;
   }


   Player<color_>& otherPlayer()
   {
      int tmp = curPlayer;
      tmp = ++tmp % 2;
      return player[tmp];
   }

   Player<color_>& currentPlayer()
   {
      return player[curPlayer];
   }


private:
   color_ pole[8][8];
   int pl1ZoneQty;
   int pl2ZoneQty;
   Player<color_> player[2];
   int curPlayer;
   Points points;


   void fillPoleArea (int8_t vPos, int8_t hPos)
   {
      fillArea (pole[vPos][hPos], vPos, hPos);
   }
};