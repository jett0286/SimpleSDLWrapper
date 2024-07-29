// GameClient.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <simplesdl.h>

#define FRAMES_PER_SECOND 60
#define TICKS_PER_FRAME (1000 / FRAMES_PER_SECOND)

int main()
{
    SSW_Window testWindow;
    SSW_Command_Quit quitCommand;
    Uint32 ticks = 0;

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

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
