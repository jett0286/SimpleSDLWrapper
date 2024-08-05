#include "cardstack.h"

CardStack::CardStack ()
{
	destRect_ = {100, 100, 100, 100};
	gfxElemBackground.setDestRect (destRect_);
	gfxElemBackground.setColor ({0x00, 0x00, 0x00, 0x88});
	gfxElemBackground.setPriority (0);
}

void CardStack::pushCard (PlayingCard* playingCard)
{
	stackCardsInPile_.push (playingCard);
	playingCard->setDestRect (destRect_);
	playingCard->enable ();
}

PlayingCard* CardStack::popCard ()
{
	PlayingCard* returnVal = stackCardsInPile_.top ();
	stackCardsInPile_.pop ();
	returnVal->disable (); // REMOVE ME
	return returnVal;
}

void CardStack::setDestRect (SDL_Rect destRect)
{
	destRect_ = destRect;
	gfxElemBackground.setDestRect (destRect_);
}

void CardStack::registerElements (SSW_Window* pWindow)
{
	pWindow->registerGraphicsElement (&gfxElemBackground);
}
