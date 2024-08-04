// GameClient.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <simplesdl.h>

#include "playingcard.h"

#define FRAMES_PER_SECOND 60
#define TICKS_PER_FRAME (1000 / FRAMES_PER_SECOND)

#undef main



int main ()
{
  SSW_Window testWindow;
  SSW_Command_Quit quitCommand;

  PlayingCard TwoDiamonds;

  testWindow.setBackgroundColor ({0x11, 0x88, 0x11});
  testWindow.mapKey (SDLK_ESCAPE, &quitCommand);
  testWindow.loadSprites ("playingCards.png", 190, 140);

  TwoDiamonds.setSprite (testWindow.getSpriteFromID (2));
  TwoDiamonds.setDestRect ({100, 100, 140, 190});
  TwoDiamonds.registerElems (&testWindow);

  while (true)
  {
    testWindow.startTimer ();
    testWindow.handleInput ();
    testWindow.refresh ();
    testWindow.endTimerAndWait ();
  }
}