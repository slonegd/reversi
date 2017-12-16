#pragma once

template <class color_>
class Player
{
public:
   const color_ col;

   Player (color_ col)
      : col(col), posY(0), posX(0)
   {

   }

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


};