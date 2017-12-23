#pragma once

#include <Iplayer.h>
#include <pole.h>

template <class color_>
class Player : public Iplayer
{
public:
   const color_ col;
   using Dir = Iplayer::Dir;

   Player (color_ col)
      : col(col), posY(0), posX(0)
   {

   }
/*
   Player (Pole& pole)
      : posY(0), posX(0), pole(pole)
   {

   }

   void go (Dir dir)
   {
      int y,x;
      pole.player[pole.curPlayer].getPosition(y, x);
      pole.fillPoleArea (y, x);
      switch (dir) {
         case Up:    y = (y + 7) % 8; break;
         case Down:  y = (y + 1) % 8; break;
         case Left:  x = (x + 7) % 8; break;
         case Right: x = (x + 1) % 8; break;
      }
      pole.player[pole.curPlayer].setPosition(y, x);
      pole.fillArea (blue, y, x);
      pole.getPoints (y, x);
      move (26, 0);
      printw ("up        %d\n", pole.points.up);
      printw ("down      %d\n", pole.points.down);
      printw ("left      %d\n", pole.points.left);
      printw ("right     %d\n", pole.points.right);
      printw ("upLeft    %d\n", pole.points.upLeft);
      printw ("upRight   %d\n", pole.points.upRight);
      printw ("downRight %d\n", pole.points.downRight);
      printw ("downLeft  %d\n", pole.points.downLeft);
      printw ("all       %d\n", pole.points.all);
   }
*/
   void go (Dir dir) {}
   void getMove() {}

   void getPosition (int& y, int& x)
   {
      y = posY;
      x = posX;
   }
   void setPosition (int& y, int& x)
   {
      posY = y;
      posX = x;
   }


private:
   int posY;
   int posX;
   // Pole& pole;


};