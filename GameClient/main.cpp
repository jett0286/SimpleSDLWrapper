// GameClient.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <simplesdl.h>

#define FRAMES_PER_SECOND 60
#define TICKS_PER_FRAME (1000 / FRAMES_PER_SECOND)

#undef main

int main ()
{
    SSW_Window testWindow;
    SSW_Command_Quit quitCommand;
    Uint32 ticks = 0;

    SSW_GraphicsElement_SolidColor red ({0xFF, 0x00, 0x00, 0xFF});
    SSW_GraphicsElement_SolidColor green ({ 0x00, 0xFF, 0x00, 0xFF });
    SSW_GraphicsElement_SolidColor blue ({ 0x00, 0x00, 0xFF, 0xFF });

    red.setDestRect ({0, 0, 100, 100});
    green.setDestRect ({50, 50, 100, 100});
    blue.setDestRect ({100, 100, 100, 100});

    blue.setPriority (100);

    testWindow.registerGraphicsElement (&red);
    testWindow.registerGraphicsElement (&green);
    testWindow.registerGraphicsElement (&blue);

    testWindow.mapKey (SDLK_ESCAPE, &quitCommand);

    while (true)
    {
      ticks = SDL_GetTicks ();
      testWindow.handleInput ();
      testWindow.refresh ();
      ticks = SDL_GetTicks () - ticks; // using ticks for 2 different things, bad example
      if (ticks < TICKS_PER_FRAME)
      {
        SDL_Delay (TICKS_PER_FRAME - ticks);
      }
    }
}