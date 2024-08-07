// GameClient.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <simplesdl.h>

#include "playingcard.h"
#include "cardstack.h"

#undef main

class CommandPopStack : public SSW_Command_Base
{
	public:
		CommandPopStack (CardStack* stackToPop)
		{
			stackToPop_ = stackToPop;
		}
		virtual void execute ()
		{
			stackToPop_->popCard ();
		}
	private:
		CardStack* stackToPop_;
};

int main ()
{
	SSW_Window testWindow;
	SSW_Command_Quit quitCommand;

	PlayingCard* dummyCard;
	CardStack stack;

	testWindow.setBackgroundColor ({0x11, 0x88, 0x11, 0xFF});
	testWindow.mapKey (SDLK_ESCAPE, &quitCommand);
	testWindow.loadSprites ("clubs.png", 124, 88, 13);
	testWindow.loadSprites ("hearts.png", 124, 88, 13);
	testWindow.loadSprites ("diamonds.png", 124, 88, 13);
	testWindow.loadSprites ("spades.png", 124, 88, 13);

	stack.setDestRect ({ 100, 100, 140, 190 });
	stack.registerElements (&testWindow);

	for (int i = 0; i < 1; i++)
	{
		dummyCard = new PlayingCard (testWindow.getSpriteFromID (i), NO_DENOM, NO_SUIT);
		
		dummyCard->setPriority (i);
		dummyCard->registerElems (&testWindow);
		
		stack.pushCard (dummyCard);
	}
	
	testWindow.mapKey (SDLK_SPACE, new CommandPopStack (&stack));

	while (true)
	{
		testWindow.startTimer ();
		testWindow.handleInput ();
		testWindow.refresh ();
		testWindow.endTimerAndWait ();
	}
}