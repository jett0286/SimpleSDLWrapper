// GameClient.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <simplesdl.h>

#define FRAMES_PER_SECOND 60
#define TICKS_PER_FRAME (1000 / FRAMES_PER_SECOND)

#undef main

class SSW_Command_PrintString : public SSW_Command_Base
{
  public:
    SSW_Command_PrintString (std::string contents)
    {
      contents_ = contents;
    }
    virtual void execute ()
    {
      std::cout << contents_ << std::endl;
    }
  private:
    std::string contents_;
};

int main ()
{
    SSW_Window testWindow;
    SSW_Command_Quit quitCommand;
    Uint32 ticks = 0;

    SSW_MouseElement clickbox1;
    SSW_MouseElement clickbox2;
    SSW_MouseElement clickbox3;
    SSW_MouseElement clickbox4;

    testWindow.mapKey (SDLK_ESCAPE, &quitCommand);

    clickbox1.setClickableRect ({ 0, 0, 100, 100 });
    clickbox1.setOnLeftClick (new SSW_Command_PrintString ("This is button 1"));
    clickbox1.setPriority (100);

    clickbox2.setClickableRect ({ 0, 0, 100, 100 });
    clickbox2.setOnLeftClick (new SSW_Command_PrintString ("This is button 2"));
    clickbox2.setPriority (3);

    clickbox3.setClickableRect ({ 0, 0, 100, 100 });
    clickbox3.setOnLeftClick (new SSW_Command_PrintString ("This is button 3"));
    clickbox3.setPriority (102);

    clickbox4.setClickableRect ({ 0, 0, 100, 100 });
    clickbox4.setOnLeftClick (new SSW_Command_PrintString ("This is button 4"));
    clickbox4.setPriority (1);

    testWindow.registerMouseElement (&clickbox1);
    testWindow.registerMouseElement (&clickbox2);
    testWindow.registerMouseElement (&clickbox3);
    testWindow.registerMouseElement (&clickbox4);

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