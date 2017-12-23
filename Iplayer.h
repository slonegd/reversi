#pragma once


class Iplayer
{
public:
   enum Dir { Up, Down, Left, Right };
   virtual void go (Dir dir) = 0;
   virtual void getMove() = 0;
   virtual ~Iplayer() {};

};